#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/RLSInteractable.h"
#include "Core/RLSTutorialComponent.h"
#include "RLSTutorialMarker.generated.h"

class UStaticMeshComponent;
UCLASS()
class REALLIFESURVIVAL_API ARLSTutorialMarker : public AActor, public IRLSInteractable
{
    GENERATED_BODY()
public:
    ARLSTutorialMarker();
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) ERLSTutorialStep Step = ERLSTutorialStep::VisitSupermarket;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Prompt;
    virtual void Interact_Implementation(AActor* InteractingActor) override;
    virtual FText GetInteractionText_Implementation() const override;
};
