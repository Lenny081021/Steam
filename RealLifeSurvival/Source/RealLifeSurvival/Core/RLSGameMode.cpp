#include "Core/RLSGameMode.h"
#include "Player/RLSCharacter.h"
#include "Inventory/RLSInventoryComponent.h"
#include "Survival/RLSSurvivalComponent.h"
#include "Saving/RLSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UI/RLSHUD.h"
#include "UI/RLSPlayerController.h"

ARLSGameMode::ARLSGameMode() { DefaultPawnClass = ARLSCharacter::StaticClass(); HUDClass = ARLSHUD::StaticClass(); PlayerControllerClass = ARLSPlayerController::StaticClass(); }
bool ARLSGameMode::SaveCurrentPlayer(const FString& SlotName)
{
    ARLSCharacter* Player = Cast<ARLSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)); if (!Player || SlotName.IsEmpty()) return false;
    URLSSaveGame* Save = Cast<URLSSaveGame>(UGameplayStatics::CreateSaveGameObject(URLSSaveGame::StaticClass())); if (!Save) return false;
    Save->PlayerLocation = Player->GetActorLocation(); Save->PlayerRotation = Player->GetActorRotation(); Save->Money = Player->Money; Save->Inventory = Player->Inventory->Items;
    Save->Health = Player->Survival->Health; Save->Hunger = Player->Survival->Hunger; Save->Thirst = Player->Survival->Thirst; Save->Stamina = Player->Survival->Stamina; Save->BodyTemperature = Player->Survival->BodyTemperature;
    return UGameplayStatics::SaveGameToSlot(Save, SlotName, 0);
}
bool ARLSGameMode::LoadCurrentPlayer(const FString& SlotName)
{
    if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0)) return false;
    URLSSaveGame* Save = Cast<URLSSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)); ARLSCharacter* Player = Cast<ARLSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (!Save || !Player || Save->SaveVersion != 1) return false;
    Player->SetActorLocationAndRotation(Save->PlayerLocation, Save->PlayerRotation); Player->Money = Save->Money; Player->Inventory->SetItems(Save->Inventory); Player->Survival->SetStats(Save->Health, Save->Hunger, Save->Thirst, Save->Stamina, Save->BodyTemperature);
    return true;
}
