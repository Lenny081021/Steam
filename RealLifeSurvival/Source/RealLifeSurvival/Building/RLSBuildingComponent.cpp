#include "Building/RLSBuildingComponent.h"
#include "Building/RLSBuildingPiece.h"
#include "Inventory/RLSInventoryComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"
#include "Core/RLSQuestComponent.h"

URLSBuildingComponent::URLSBuildingComponent() { SetIsReplicatedByDefault(true); DefaultBuildingClass = ARLSBuildingPiece::StaticClass(); DefaultCost.Add({TEXT("Plank"), 4}); }
bool URLSBuildingComponent::PlaceDefaultBuilding(const FTransform& Transform)
{
    APawn* Pawn = Cast<APawn>(GetOwner()); if (!Pawn || !Pawn->HasAuthority() || !DefaultBuildingClass) return false;
    URLSInventoryComponent* Inventory = Pawn->FindComponentByClass<URLSInventoryComponent>(); if (!Inventory || !Inventory->HasItems(DefaultCost)) return false;
    FActorSpawnParameters Params; Params.Owner = Pawn; Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
    ARLSBuildingPiece* Piece = GetWorld()->SpawnActor<ARLSBuildingPiece>(DefaultBuildingClass, Transform, Params);
    if (!Piece) return false;
    Inventory->ConsumeItems(DefaultCost);
    if (APlayerState* State = Pawn->GetPlayerState()) Piece->OwnerPlayerId = State->GetUniqueId().ToString();
    if (URLSQuestComponent* Quests = Pawn->FindComponentByClass<URLSQuestComponent>()) Quests->NotifyBuildingPlaced();
    return true;
}
