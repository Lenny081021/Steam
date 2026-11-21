#include "World/RLSTrafficVehicle.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"

ARLSTrafficVehicle::ARLSTrafficVehicle()
{
    bReplicates=true; SetReplicateMovement(true); PrimaryActorTick.bCanEverTick=true; Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); RootComponent=Mesh; Mesh->SetCollisionProfileName(TEXT("BlockAll"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube")); if (Cube.Succeeded()) Mesh->SetStaticMesh(Cube.Object); Mesh->SetRelativeScale3D(FVector(1.9f,.85f,.5f));
}
bool ARLSTrafficVehicle::IsRouteBlocked() const
{
    FHitResult Hit; FCollisionQueryParams P(SCENE_QUERY_STAT(TrafficAvoid),false,this);
    return GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(),GetActorLocation()+GetActorForwardVector()*StopDistance,ECC_Visibility,P) && Hit.GetActor()!=nullptr;
}
void ARLSTrafficVehicle::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds); if (!HasAuthority() || RoutePoints.Num()<2 || IsRouteBlocked()) return;
    const FVector Target=RoutePoints[CurrentRouteIndex]; FVector Direction=Target-GetActorLocation(); Direction.Z=0;
    if (Direction.SizeSquared()<FMath::Square(120.0f)) { CurrentRouteIndex=(CurrentRouteIndex+1)%RoutePoints.Num(); return; }
    const FRotator Facing=Direction.Rotation(); SetActorRotation(FMath::RInterpTo(GetActorRotation(),Facing,DeltaSeconds,3.0f)); AddActorWorldOffset(GetActorForwardVector()*(SpeedKmh/3.6f)*100.0f*DeltaSeconds,true);
}
void ARLSTrafficVehicle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const { Super::GetLifetimeReplicatedProps(Out); DOREPLIFETIME(ARLSTrafficVehicle,CurrentRouteIndex); }
