#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/RLSItemTypes.h"
#include "RLSBuildingComponent.generated.h"

class ARLSBuildingPiece;
UCLASS(ClassGroup=(RLS), meta=(BlueprintSpawnableComponent))
class REALLIFESURVIVAL_API URLSBuildingComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    URLSBuildingComponent();
    UPROPERTY(EditDefaultsOnly, Category="Building") TSubclassOf<ARLSBuildingPiece> DefaultBuildingClass;
    UPROPERTY(EditDefaultsOnly, Category="Building") TArray<FRLSItemStack> DefaultCost;
    UFUNCTION(BlueprintCallable, Category="Building") bool PlaceDefaultBuilding(const FTransform& Transform);
};
