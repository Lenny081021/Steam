#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/RLSInteractable.h"
#include "RLSResourceNode.generated.h"

class UStaticMeshComponent;
UCLASS()
class REALLIFESURVIVAL_API ARLSResourceNode : public AActor, public IRLSInteractable
{
    GENERATED_BODY()
public:
    ARLSResourceNode();
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource") FName ItemId = TEXT("Wood");
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource") int32 YieldPerUse = 1;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource") int32 RemainingUses = 5;
    virtual void Interact_Implementation(AActor* InteractingActor) override;
    virtual FText GetInteractionText_Implementation() const override;
};
