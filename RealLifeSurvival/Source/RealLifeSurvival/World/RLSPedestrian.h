#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RLSPedestrian.generated.h"

class UStaticMeshComponent;
UCLASS()
class REALLIFESURVIVAL_API ARLSPedestrian : public ACharacter
{
    GENERATED_BODY()
public:
    ARLSPedestrian();
    virtual void BeginPlay() override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NPC") TArray<FVector> PatrolPoints;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NPC") float PauseSeconds = 3.0f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UStaticMeshComponent> VisibleBody;
private:
    void MoveToNextPoint();
    int32 CurrentPoint = 0;
    FTimerHandle PatrolTimer;
};
