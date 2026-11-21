#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLSSurvivalComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRLSSurvivalChanged);

UCLASS(ClassGroup=(RLS), meta=(BlueprintSpawnableComponent))
class REALLIFESURVIVAL_API URLSSurvivalComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    URLSSurvivalComponent();
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Survival") float HungerDecayPerMinute = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Survival") float ThirstDecayPerMinute = 1.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Survival") float StarvationDamagePerSecond = 2.0f;
    UPROPERTY(ReplicatedUsing=OnRep_Stats, VisibleAnywhere, BlueprintReadOnly, Category="Survival") float Health = 100.0f;
    UPROPERTY(ReplicatedUsing=OnRep_Stats, VisibleAnywhere, BlueprintReadOnly, Category="Survival") float Hunger = 100.0f;
    UPROPERTY(ReplicatedUsing=OnRep_Stats, VisibleAnywhere, BlueprintReadOnly, Category="Survival") float Thirst = 100.0f;
    UPROPERTY(ReplicatedUsing=OnRep_Stats, VisibleAnywhere, BlueprintReadOnly, Category="Survival") float Stamina = 100.0f;
    UPROPERTY(ReplicatedUsing=OnRep_Stats, VisibleAnywhere, BlueprintReadOnly, Category="Survival") float BodyTemperature = 37.0f;
    UPROPERTY(BlueprintAssignable) FRLSSurvivalChanged OnSurvivalChanged;

    UFUNCTION(BlueprintCallable, Category="Survival") void RestoreHunger(float Amount);
    UFUNCTION(BlueprintCallable, Category="Survival") void RestoreThirst(float Amount);
    UFUNCTION(BlueprintCallable, Category="Survival") void ApplyDamage(float Amount);
    UFUNCTION(BlueprintCallable, Category="Survival") void SetStats(float NewHealth, float NewHunger, float NewThirst, float NewStamina, float NewTemperature);
private:
    FTimerHandle SurvivalTimer;
    void UpdateSurvival();
    UFUNCTION() void OnRep_Stats();
};
