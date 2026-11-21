#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLSCraftingComponent.generated.h"

class UDataTable;
UCLASS(ClassGroup=(RLS), meta=(BlueprintSpawnableComponent))
class REALLIFESURVIVAL_API URLSCraftingComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    URLSCraftingComponent();
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Crafting") TObjectPtr<UDataTable> Recipes;
    UFUNCTION(BlueprintCallable, Category="Crafting") bool Craft(FName RecipeId);
};
