#include "Core/RLSQuestComponent.h"
#include "Inventory/RLSInventoryComponent.h"
#include "GameFramework/Actor.h"

void URLSQuestComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner() && GetOwner()->HasAuthority())
    {
        Quests = {{TEXT("GatherWood"), NSLOCTEXT("RLS", "QuestWood", "Sammle 20 Holz"), ERLSQuestState::Active}, {TEXT("CraftPlanks"), NSLOCTEXT("RLS", "QuestPlank", "Stelle Bretter her"), ERLSQuestState::Active}, {TEXT("BuildShelter"), NSLOCTEXT("RLS", "QuestBuild", "Errichte eine Wand"), ERLSQuestState::Active}};
        if (URLSInventoryComponent* Inventory = GetOwner()->FindComponentByClass<URLSInventoryComponent>()) Inventory->OnInventoryChanged.AddDynamic(this, &URLSQuestComponent::CheckInventoryQuests);
    }
}
void URLSQuestComponent::CheckInventoryQuests()
{
    if (URLSInventoryComponent* Inventory = GetOwner()->FindComponentByClass<URLSInventoryComponent>()) { if (Inventory->GetQuantity(TEXT("Wood")) >= 20) Complete(TEXT("GatherWood")); if (Inventory->GetQuantity(TEXT("Plank")) >= 1) Complete(TEXT("CraftPlanks")); }
}
void URLSQuestComponent::NotifyBuildingPlaced() { if (GetOwner() && GetOwner()->HasAuthority()) Complete(TEXT("BuildShelter")); }
void URLSQuestComponent::Complete(FName QuestId) { for (FRLSQuestStatus& Quest : Quests) if (Quest.QuestId == QuestId) { Quest.State = ERLSQuestState::Completed; return; } }
