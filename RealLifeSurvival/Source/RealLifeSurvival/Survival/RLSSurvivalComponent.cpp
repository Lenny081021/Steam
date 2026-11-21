#include "Survival/RLSSurvivalComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

URLSSurvivalComponent::URLSSurvivalComponent() { SetIsReplicatedByDefault(true); }
void URLSSurvivalComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner() && GetOwner()->HasAuthority()) GetWorld()->GetTimerManager().SetTimer(SurvivalTimer, this, &URLSSurvivalComponent::UpdateSurvival, 1.0f, true);
}
void URLSSurvivalComponent::UpdateSurvival()
{
    Hunger = FMath::Max(0.0f, Hunger - HungerDecayPerMinute / 60.0f);
    Thirst = FMath::Max(0.0f, Thirst - ThirstDecayPerMinute / 60.0f);
    if (Hunger <= 0.0f || Thirst <= 0.0f) Health = FMath::Max(0.0f, Health - StarvationDamagePerSecond);
    OnSurvivalChanged.Broadcast();
}
void URLSSurvivalComponent::RestoreHunger(float Amount) { if (GetOwner()->HasAuthority()) { Hunger = FMath::Clamp(Hunger + Amount, 0.0f, 100.0f); OnSurvivalChanged.Broadcast(); } }
void URLSSurvivalComponent::RestoreThirst(float Amount) { if (GetOwner()->HasAuthority()) { Thirst = FMath::Clamp(Thirst + Amount, 0.0f, 100.0f); OnSurvivalChanged.Broadcast(); } }
void URLSSurvivalComponent::ApplyDamage(float Amount) { if (GetOwner()->HasAuthority()) { Health = FMath::Max(0.0f, Health - FMath::Max(0.0f, Amount)); OnSurvivalChanged.Broadcast(); } }
void URLSSurvivalComponent::SetStats(float NewHealth, float NewHunger, float NewThirst, float NewStamina, float NewTemperature)
{ if (GetOwner()->HasAuthority()) { Health=FMath::Clamp(NewHealth,0.0f,100.0f); Hunger=FMath::Clamp(NewHunger,0.0f,100.0f); Thirst=FMath::Clamp(NewThirst,0.0f,100.0f); Stamina=FMath::Clamp(NewStamina,0.0f,100.0f); BodyTemperature=NewTemperature; OnSurvivalChanged.Broadcast(); } }
void URLSSurvivalComponent::OnRep_Stats() { OnSurvivalChanged.Broadcast(); }
void URLSSurvivalComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const { Super::GetLifetimeReplicatedProps(OutLifetimeProps); DOREPLIFETIME(URLSSurvivalComponent, Health); DOREPLIFETIME(URLSSurvivalComponent, Hunger); DOREPLIFETIME(URLSSurvivalComponent, Thirst); DOREPLIFETIME(URLSSurvivalComponent, Stamina); DOREPLIFETIME(URLSSurvivalComponent, BodyTemperature); }
