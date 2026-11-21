#include "World/RLSTutorialMarker.h"
#include "Player/RLSCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ARLSTutorialMarker::ARLSTutorialMarker() { bReplicates=true; Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); RootComponent=Mesh; static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere")); if (Sphere.Succeeded()) Mesh->SetStaticMesh(Sphere.Object); Mesh->SetCollisionProfileName(TEXT("BlockAll")); Mesh->SetRelativeScale3D(FVector(.7f)); }
void ARLSTutorialMarker::Interact_Implementation(AActor* InteractingActor) { if (HasAuthority()) if (ARLSCharacter* Character=Cast<ARLSCharacter>(InteractingActor)) if (Character->Tutorial) Character->Tutorial->AdvanceTo(Step); }
FText ARLSTutorialMarker::GetInteractionText_Implementation() const { return Prompt.IsEmpty() ? NSLOCTEXT("RLS","TutorialMarker","Tutorialschritt ausführen") : Prompt; }
