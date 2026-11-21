#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLSBuildingPiece.generated.h"

class UStaticMeshComponent;
UCLASS()
class REALLIFESURVIVAL_API ARLSBuildingPiece : public AActor
{
    GENERATED_BODY()
public:
    ARLSBuildingPiece();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly) FString OwnerPlayerId;
};
