#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/RLSInteractable.h"
#include "RLSMerchant.generated.h"

class UStaticMeshComponent;
UCLASS()
class REALLIFESURVIVAL_API ARLSMerchant : public AActor, public IRLSInteractable
{
    GENERATED_BODY()
public:
    ARLSMerchant();
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Economy") FName AcceptedItem = TEXT("Wood");
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Economy") int32 PricePerItem = 5;
    virtual void Interact_Implementation(AActor* InteractingActor) override;
    virtual FText GetInteractionText_Implementation() const override;
};
