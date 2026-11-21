#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/RLSInteractable.h"
#include "RLSProperty.generated.h"

class UStaticMeshComponent;
UCLASS()
class REALLIFESURVIVAL_API ARLSProperty : public AActor, public IRLSInteractable
{
    GENERATED_BODY()
public:
    ARLSProperty();
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Property") FText PropertyName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Property") int32 PurchasePrice = 50000;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Property") FString OwnerId;
    virtual void Interact_Implementation(AActor* InteractingActor) override;
    virtual FText GetInteractionText_Implementation() const override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
