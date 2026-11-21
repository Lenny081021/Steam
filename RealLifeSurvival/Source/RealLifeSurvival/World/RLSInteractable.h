#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RLSInteractable.generated.h"

UINTERFACE(BlueprintType)
class REALLIFESURVIVAL_API URLSInteractable : public UInterface { GENERATED_BODY() };

class REALLIFESURVIVAL_API IRLSInteractable
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") void Interact(AActor* InteractingActor);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") FText GetInteractionText() const;
};
