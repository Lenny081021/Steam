#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLSItemTypes.h"
#include "RLSInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRLSInventoryChanged);

UCLASS(ClassGroup=(RLS), meta=(BlueprintSpawnableComponent))
class REALLIFESURVIVAL_API URLSInventoryComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    URLSInventoryComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory") int32 MaxSlots = 30;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory") float MaxWeight = 40.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory") TObjectPtr<UDataTable> ItemDefinitions;
    UPROPERTY(ReplicatedUsing=OnRep_Items, VisibleAnywhere, BlueprintReadOnly, Category="Inventory") TArray<FRLSItemStack> Items;
    UPROPERTY(BlueprintAssignable) FRLSInventoryChanged OnInventoryChanged;

    UFUNCTION(BlueprintCallable, Category="Inventory") bool AddItem(FName ItemId, int32 Quantity);
    UFUNCTION(BlueprintCallable, Category="Inventory") bool RemoveItem(FName ItemId, int32 Quantity);
    UFUNCTION(BlueprintPure, Category="Inventory") int32 GetQuantity(FName ItemId) const;
    UFUNCTION(BlueprintPure, Category="Inventory") float GetCurrentWeight() const;
    UFUNCTION(BlueprintPure, Category="Inventory") bool HasItems(const TArray<FRLSItemStack>& Required) const;
    UFUNCTION(BlueprintCallable, Category="Inventory") bool ConsumeItems(const TArray<FRLSItemStack>& Required);
    UFUNCTION(BlueprintCallable, Category="Inventory") void SetItems(const TArray<FRLSItemStack>& NewItems);
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
    UFUNCTION() void OnRep_Items();
    const FRLSItemDefinition* FindDefinition(FName ItemId) const;
};
