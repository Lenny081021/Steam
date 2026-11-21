#include "World/RLSDayNightActor.h"
#include "Engine/DirectionalLight.h"
#include "Net/UnrealNetwork.h"

ARLSDayNightActor::ARLSDayNightActor() { PrimaryActorTick.bCanEverTick = true; bReplicates = true; }
void ARLSDayNightActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!HasAuthority()) return;
    TimeOfDay = FMath::Fmod(TimeOfDay + DeltaSeconds * 24.0f / (FullDayMinutes * 60.0f), 24.0f);
    if (Sun) Sun->SetActorRotation(FRotator((TimeOfDay / 24.0f) * 360.0f - 90.0f, -35.0f, 0.0f));
}
void ARLSDayNightActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const { Super::GetLifetimeReplicatedProps(OutLifetimeProps); DOREPLIFETIME(ARLSDayNightActor, TimeOfDay); }
