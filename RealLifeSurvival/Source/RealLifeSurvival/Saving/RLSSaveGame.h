#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Inventory/RLSItemTypes.h"
#include "RLSSaveGame.generated.h"

UCLASS()
class REALLIFESURVIVAL_API URLSSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere) int32 SaveVersion = 1;
    UPROPERTY(VisibleAnywhere) FVector PlayerLocation = FVector::ZeroVector;
    UPROPERTY(VisibleAnywhere) FRotator PlayerRotation = FRotator::ZeroRotator;
    UPROPERTY(VisibleAnywhere) float Health = 100.0f;
    UPROPERTY(VisibleAnywhere) float Hunger = 100.0f;
    UPROPERTY(VisibleAnywhere) float Thirst = 100.0f;
    UPROPERTY(VisibleAnywhere) float Stamina = 100.0f;
    UPROPERTY(VisibleAnywhere) float BodyTemperature = 37.0f;
    UPROPERTY(VisibleAnywhere) int32 Money = 250;
    UPROPERTY(VisibleAnywhere) TArray<FRLSItemStack> Inventory;
};
