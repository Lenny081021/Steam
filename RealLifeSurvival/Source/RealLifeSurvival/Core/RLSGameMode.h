#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RLSGameMode.generated.h"

UCLASS()
class REALLIFESURVIVAL_API ARLSGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ARLSGameMode();
    UFUNCTION(BlueprintCallable, Category="Save") bool SaveCurrentPlayer(const FString& SlotName);
    UFUNCTION(BlueprintCallable, Category="Save") bool LoadCurrentPlayer(const FString& SlotName);
};
