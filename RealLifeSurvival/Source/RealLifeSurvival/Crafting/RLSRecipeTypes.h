#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Inventory/RLSItemTypes.h"
#include "RLSRecipeTypes.generated.h"

USTRUCT(BlueprintType)
struct FRLSRecipeDefinition : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName RecipeId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FRLSItemStack> Ingredients;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FRLSItemStack Output;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0.0")) float CraftSeconds = 1.0f;
};
