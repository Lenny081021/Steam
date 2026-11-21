#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLSDayNightActor.generated.h"

class ADirectionalLight;
UCLASS()
class REALLIFESURVIVAL_API ARLSDayNightActor : public AActor
{
    GENERATED_BODY()
public:
    ARLSDayNightActor();
    virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time", meta=(ClampMin="1.0")) float FullDayMinutes = 60.0f;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Time", meta=(ClampMin="0.0", ClampMax="24.0")) float TimeOfDay = 8.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time") TObjectPtr<ADirectionalLight> Sun;
};
