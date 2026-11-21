#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLSTrafficVehicle.generated.h"

class UStaticMeshComponent;
/** Lightweight server-authoritative traffic agent for spline/waypoint roads.
 * It is intentionally separate from the player vehicle until Chaos vehicle assets are available. */
UCLASS()
class REALLIFESURVIVAL_API ARLSTrafficVehicle : public AActor
{
    GENERATED_BODY()
public:
    ARLSTrafficVehicle();
    virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic") TArray<FVector> RoutePoints;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic", meta=(ClampMin="1.0")) float SpeedKmh = 35.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic", meta=(ClampMin="50.0")) float StopDistance = 350.0f;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Traffic") int32 CurrentRouteIndex = 0;
private:
    bool IsRouteBlocked() const;
};
