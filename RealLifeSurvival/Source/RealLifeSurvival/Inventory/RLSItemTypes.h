#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RLSItemTypes.generated.h"

UENUM(BlueprintType)
enum class ERLSItemCategory : uint8
{
    Resource, Tool, Food, Material, Building, VehiclePart, Agriculture, Furniture, Rare
};

USTRUCT(BlueprintType)
struct FRLSItemDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName ItemId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Description;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) ERLSItemCategory Category = ERLSItemCategory::Resource;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="1")) int32 MaxStack = 99;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0.0")) float UnitWeight = 0.1f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0")) int32 BuyPrice = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0")) int32 SellPrice = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float HungerRestore = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float ThirstRestore = 0.0f;
};

USTRUCT(BlueprintType)
struct FRLSItemStack
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ItemId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0")) int32 Quantity = 0;

    bool IsValid() const { return !ItemId.IsNone() && Quantity > 0; }
};
