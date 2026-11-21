#include "Building/RLSBuildingPiece.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"

ARLSBuildingPiece::ARLSBuildingPiece() { bReplicates = true; Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); RootComponent = Mesh; Mesh->SetCollisionProfileName(TEXT("BlockAll")); static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube")); if (Cube.Succeeded()) Mesh->SetStaticMesh(Cube.Object); Mesh->SetRelativeScale3D(FVector(2.0f, .25f, 1.5f)); }
void ARLSBuildingPiece::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const { Super::GetLifetimeReplicatedProps(Out); DOREPLIFETIME(ARLSBuildingPiece, OwnerPlayerId); }
