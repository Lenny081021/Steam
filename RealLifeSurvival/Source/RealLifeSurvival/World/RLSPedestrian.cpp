#include "World/RLSPedestrian.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

ARLSPedestrian::ARLSPedestrian()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; VisibleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleBody")); VisibleBody->SetupAttachment(GetCapsuleComponent());
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube")); if (Cube.Succeeded()) VisibleBody->SetStaticMesh(Cube.Object); VisibleBody->SetRelativeLocation(FVector(0,0,-40)); VisibleBody->SetRelativeScale3D(FVector(.35f,.35f,.9f)); VisibleBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ARLSPedestrian::BeginPlay() { Super::BeginPlay(); if (PatrolPoints.Num() > 0) GetWorldTimerManager().SetTimer(PatrolTimer, this, &ARLSPedestrian::MoveToNextPoint, PauseSeconds, true, .5f); }
void ARLSPedestrian::MoveToNextPoint()
{
    if (PatrolPoints.IsEmpty()) return; if (AAIController* AI = Cast<AAIController>(GetController())) { UNavigationSystemV1::SimpleMoveToLocation(AI, PatrolPoints[CurrentPoint]); CurrentPoint = (CurrentPoint + 1) % PatrolPoints.Num(); }
}
