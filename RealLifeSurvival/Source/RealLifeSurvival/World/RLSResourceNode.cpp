#include "World/RLSResourceNode.h"
#include "Components/StaticMeshComponent.h"
#include "Inventory/RLSInventoryComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

ARLSResourceNode::ARLSResourceNode()
{
    bReplicates = true; Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); RootComponent = Mesh; Mesh->SetCollisionProfileName(TEXT("BlockAll")); static ConstructorHelpers::FObjectFinder<UStaticMesh> Rock(TEXT("/Engine/BasicShapes/Sphere.Sphere")); if (Rock.Succeeded()) Mesh->SetStaticMesh(Rock.Object); Mesh->SetRelativeScale3D(FVector(1.25f));
}
void ARLSResourceNode::Interact_Implementation(AActor* InteractingActor)
{
    if (!HasAuthority() || RemainingUses <= 0 || !InteractingActor) return;
    if (URLSInventoryComponent* Inventory = InteractingActor->FindComponentByClass<URLSInventoryComponent>())
    {
        if (Inventory->AddItem(ItemId, YieldPerUse)) { --RemainingUses; if (RemainingUses == 0) Destroy(); }
    }
}
FText ARLSResourceNode::GetInteractionText_Implementation() const { return FText::Format(NSLOCTEXT("RLS", "Harvest", "Sammle {0}"), FText::FromName(ItemId)); }
