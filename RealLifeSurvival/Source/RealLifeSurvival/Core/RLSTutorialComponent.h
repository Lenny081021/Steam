#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLSTutorialComponent.generated.h"

UENUM(BlueprintType)
enum class ERLSTutorialStep : uint8 { LeaveApartment, VisitSupermarket, MeetClient, CollectVehicle, DeliverPackage, Complete };

UCLASS(ClassGroup=(RLS), meta=(BlueprintSpawnableComponent))
class REALLIFESURVIVAL_API URLSTutorialComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    URLSTutorialComponent();
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Tutorial") ERLSTutorialStep CurrentStep = ERLSTutorialStep::LeaveApartment;
    UFUNCTION(BlueprintCallable, Category="Tutorial") bool AdvanceTo(ERLSTutorialStep ReachedStep);
    UFUNCTION(BlueprintPure, Category="Tutorial") FText GetObjectiveText() const;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
