#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLSQuestComponent.generated.h"

UENUM(BlueprintType)
enum class ERLSQuestState : uint8 { Active, Completed };

USTRUCT(BlueprintType)
struct FRLSQuestStatus
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FName QuestId;
    UPROPERTY(BlueprintReadOnly) FText Title;
    UPROPERTY(BlueprintReadOnly) ERLSQuestState State = ERLSQuestState::Active;
};

UCLASS(ClassGroup=(RLS), meta=(BlueprintSpawnableComponent))
class REALLIFESURVIVAL_API URLSQuestComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quests") TArray<FRLSQuestStatus> Quests;
    UFUNCTION(BlueprintCallable, Category="Quests") void NotifyBuildingPlaced();
private:
    UFUNCTION() void CheckInventoryQuests();
    void Complete(FName QuestId);
};
