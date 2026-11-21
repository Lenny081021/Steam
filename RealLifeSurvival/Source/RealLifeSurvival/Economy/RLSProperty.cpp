#include "Economy/RLSProperty.h"
#include "Player/RLSCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"

ARLSProperty::ARLSProperty(){ bReplicates=true; Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); RootComponent=Mesh; static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube")); if(Cube.Succeeded())Mesh->SetStaticMesh(Cube.Object); Mesh->SetCollisionProfileName(TEXT("BlockAll")); }
void ARLSProperty::Interact_Implementation(AActor* InteractingActor){ if(!HasAuthority()||!OwnerId.IsEmpty())return; if(ARLSCharacter* P=Cast<ARLSCharacter>(InteractingActor))if(P->SpendMoney(PurchasePrice))if(APlayerState* S=P->GetPlayerState())OwnerId=S->GetUniqueId().ToString(); }
FText ARLSProperty::GetInteractionText_Implementation() const { return OwnerId.IsEmpty()?FText::Format(NSLOCTEXT("RLS","BuyProperty","Kaufe Immobilie für {0} €"),FText::AsNumber(PurchasePrice)):NSLOCTEXT("RLS","OwnedProperty","Immobilie im Besitz"); }
void ARLSProperty::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const {Super::GetLifetimeReplicatedProps(Out);DOREPLIFETIME(ARLSProperty,OwnerId);}
