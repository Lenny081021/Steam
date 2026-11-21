#include "Inventory/RLSInventoryComponent.h"
#include "Net/UnrealNetwork.h"

URLSInventoryComponent::URLSInventoryComponent()
{
    SetIsReplicatedByDefault(true);
}

const FRLSItemDefinition* URLSInventoryComponent::FindDefinition(FName ItemId) const
{
    if (ItemDefinitions)
    {
        if (const FRLSItemDefinition* Found = ItemDefinitions->FindRow<FRLSItemDefinition>(ItemId, TEXT("Inventory"), false)) return Found;
    }
    // Starter definitions keep the prototype usable before an asset DataTable is created.
    static const TMap<FName, FRLSItemDefinition> Defaults = []
    {
        TMap<FName, FRLSItemDefinition> Result;
        auto Add = [&Result](FName Id, int32 Stack, float Weight, int32 Sell, float Hunger, float Thirst)
        { FRLSItemDefinition D; D.ItemId=Id; D.DisplayName=FText::FromName(Id); D.MaxStack=Stack; D.UnitWeight=Weight; D.SellPrice=Sell; D.HungerRestore=Hunger; D.ThirstRestore=Thirst; Result.Add(Id, D); };
        Add(TEXT("Wood"), 99, .5f, 5, 0, 0); Add(TEXT("Stone"), 99, .8f, 3, 0, 0); Add(TEXT("Food"), 20, .2f, 8, 25, 5); Add(TEXT("Plank"), 99, .4f, 8, 0, 0); Add(TEXT("Wall"), 20, 5.0f, 25, 0, 0); Add(TEXT("MobilePhone"), 1, .2f, 0, 0, 0); Add(TEXT("Backpack"), 1, .8f, 0, 0, 0); return Result;
    }();
    return Defaults.Find(ItemId);
}

float URLSInventoryComponent::GetCurrentWeight() const
{
    float Weight = 0.0f;
    for (const FRLSItemStack& Stack : Items)
    {
        if (const FRLSItemDefinition* Definition = FindDefinition(Stack.ItemId)) Weight += Definition->UnitWeight * Stack.Quantity;
    }
    return Weight;
}

int32 URLSInventoryComponent::GetQuantity(FName ItemId) const
{
    for (const FRLSItemStack& Stack : Items) if (Stack.ItemId == ItemId) return Stack.Quantity;
    return 0;
}

bool URLSInventoryComponent::AddItem(FName ItemId, int32 Quantity)
{
    if (Quantity <= 0 || !GetOwner() || !GetOwner()->HasAuthority()) return false;
    const FRLSItemDefinition* Definition = FindDefinition(ItemId);
    if (!Definition || GetCurrentWeight() + Definition->UnitWeight * Quantity > MaxWeight) return false;
    for (FRLSItemStack& Stack : Items)
    {
        if (Stack.ItemId == ItemId && Stack.Quantity < Definition->MaxStack)
        {
            const int32 Added = FMath::Min(Quantity, Definition->MaxStack - Stack.Quantity);
            Stack.Quantity += Added; Quantity -= Added;
            if (Quantity == 0) { OnInventoryChanged.Broadcast(); return true; }
        }
    }
    while (Quantity > 0 && Items.Num() < MaxSlots)
    {
        const int32 Added = FMath::Min(Quantity, Definition->MaxStack);
        Items.Add({ItemId, Added}); Quantity -= Added;
    }
    OnInventoryChanged.Broadcast();
    return Quantity == 0;
}

bool URLSInventoryComponent::RemoveItem(FName ItemId, int32 Quantity)
{
    if (Quantity <= 0 || !GetOwner() || !GetOwner()->HasAuthority() || GetQuantity(ItemId) < Quantity) return false;
    for (int32 Index = Items.Num() - 1; Index >= 0 && Quantity > 0; --Index)
    {
        FRLSItemStack& Stack = Items[Index]; if (Stack.ItemId != ItemId) continue;
        const int32 Removed = FMath::Min(Quantity, Stack.Quantity); Stack.Quantity -= Removed; Quantity -= Removed;
        if (Stack.Quantity == 0) Items.RemoveAt(Index);
    }
    OnInventoryChanged.Broadcast(); return true;
}

bool URLSInventoryComponent::HasItems(const TArray<FRLSItemStack>& Required) const
{
    for (const FRLSItemStack& Stack : Required) if (!Stack.IsValid() || GetQuantity(Stack.ItemId) < Stack.Quantity) return false;
    return true;
}

bool URLSInventoryComponent::ConsumeItems(const TArray<FRLSItemStack>& Required)
{
    if (!HasItems(Required)) return false;
    for (const FRLSItemStack& Stack : Required) if (!RemoveItem(Stack.ItemId, Stack.Quantity)) return false;
    return true;
}

void URLSInventoryComponent::SetItems(const TArray<FRLSItemStack>& NewItems) { if (GetOwner() && GetOwner()->HasAuthority()) { Items = NewItems; OnInventoryChanged.Broadcast(); } }
void URLSInventoryComponent::OnRep_Items() { OnInventoryChanged.Broadcast(); }
void URLSInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const { Super::GetLifetimeReplicatedProps(OutLifetimeProps); DOREPLIFETIME(URLSInventoryComponent, Items); }
