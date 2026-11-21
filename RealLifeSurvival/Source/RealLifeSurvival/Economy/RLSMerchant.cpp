#include "Economy/RLSMerchant.h"
#include "Components/StaticMeshComponent.h"
#include "Inventory/RLSInventoryComponent.h"
#include "Player/RLSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARLSMerchant::ARLSMerchant() { bReplicates = true; Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); RootComponent = Mesh; Mesh->SetCollisionProfileName(TEXT("BlockAll")); static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube")); if (Cube.Succeeded()) Mesh->SetStaticMesh(Cube.Object); Mesh->SetRelativeScale3D(FVector(1,1,2)); }
void ARLSMerchant::Interact_Implementation(AActor* InteractingActor)
{
    if (!HasAuthority()) return;
    ARLSCharacter* Player = Cast<ARLSCharacter>(InteractingActor); if (!Player) return;
    const int32 Quantity = Player->Inventory->GetQuantity(AcceptedItem);
    if (Quantity > 0 && Player->Inventory->RemoveItem(AcceptedItem, Quantity)) Player->AddMoney(Quantity * FMath::Max(0, PricePerItem));
}
FText ARLSMerchant::GetInteractionText_Implementation() const { return FText::Format(NSLOCTEXT("RLS", "Sell", "Verkaufe {0}"), FText::FromName(AcceptedItem)); }
