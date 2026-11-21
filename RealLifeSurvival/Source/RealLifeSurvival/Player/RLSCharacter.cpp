#include "Player/RLSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/RLSInventoryComponent.h"
#include "Survival/RLSSurvivalComponent.h"
#include "Crafting/RLSCraftingComponent.h"
#include "Building/RLSBuildingComponent.h"
#include "Core/RLSQuestComponent.h"
#include "Core/RLSTutorialComponent.h"
#include "World/RLSInteractable.h"
#include "Net/UnrealNetwork.h"

ARLSCharacter::ARLSCharacter()
{
    bReplicates = true;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent()); FirstPersonCamera->SetRelativeLocation(FVector(0, 0, 64)); FirstPersonCamera->bUsePawnControlRotation = true;
    ThirdPersonBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonBoom"));
    ThirdPersonBoom->SetupAttachment(GetCapsuleComponent()); ThirdPersonBoom->TargetArmLength = 280.0f; ThirdPersonBoom->SetRelativeLocation(FVector(0,0,60)); ThirdPersonBoom->bUsePawnControlRotation = true;
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera")); ThirdPersonCamera->SetupAttachment(ThirdPersonBoom); ThirdPersonCamera->bUsePawnControlRotation = false; ThirdPersonCamera->SetActive(false);
    Inventory = CreateDefaultSubobject<URLSInventoryComponent>(TEXT("Inventory"));
    Survival = CreateDefaultSubobject<URLSSurvivalComponent>(TEXT("Survival"));
    Crafting = CreateDefaultSubobject<URLSCraftingComponent>(TEXT("Crafting"));
    Building = CreateDefaultSubobject<URLSBuildingComponent>(TEXT("Building"));
    Quests = CreateDefaultSubobject<URLSQuestComponent>(TEXT("Quests"));
    Tutorial = CreateDefaultSubobject<URLSTutorialComponent>(TEXT("Tutorial"));
}
void ARLSCharacter::BeginPlay() { Super::BeginPlay(); if (HasAuthority() && Inventory->Items.IsEmpty()) { Inventory->AddItem(TEXT("MobilePhone"),1); Inventory->AddItem(TEXT("Backpack"),1); Inventory->AddItem(TEXT("Food"),2); } }
void ARLSCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis(TEXT("MoveForward"), this, &ARLSCharacter::MoveForward); Input->BindAxis(TEXT("MoveRight"), this, &ARLSCharacter::MoveRight);
    Input->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput); Input->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    Input->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump); Input->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
    Input->BindAction(TEXT("Sprint"), IE_Pressed, this, &ARLSCharacter::BeginSprint); Input->BindAction(TEXT("Sprint"), IE_Released, this, &ARLSCharacter::EndSprint);
    Input->BindAction(TEXT("Crouch"), IE_Pressed, this, &ARLSCharacter::ToggleCrouch); Input->BindAction(TEXT("Interact"), IE_Pressed, this, &ARLSCharacter::TryInteract);
    Input->BindAction(TEXT("TogglePerspective"), IE_Pressed, this, &ARLSCharacter::TogglePerspective); Input->BindAction(TEXT("UseFood"), IE_Pressed, this, &ARLSCharacter::UseFood);
    Input->BindAction(TEXT("CraftPlank"), IE_Pressed, this, &ARLSCharacter::CraftPlank); Input->BindAction(TEXT("Build"), IE_Pressed, this, &ARLSCharacter::BuildAtLookTarget);
}
void ARLSCharacter::MoveForward(float Value) { if (Controller && Value != 0) { const FRotator Rotation(0, Controller->GetControlRotation().Yaw, 0); AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X), Value); } }
void ARLSCharacter::MoveRight(float Value) { if (Controller && Value != 0) { const FRotator Rotation(0, Controller->GetControlRotation().Yaw, 0); AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y), Value); } }
void ARLSCharacter::BeginSprint() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
void ARLSCharacter::EndSprint() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
void ARLSCharacter::ToggleCrouch() { bIsCrouched ? UnCrouch() : Crouch(); }
void ARLSCharacter::TogglePerspective() { bFirstPerson = !bFirstPerson; FirstPersonCamera->SetActive(bFirstPerson); ThirdPersonCamera->SetActive(!bFirstPerson); }
void ARLSCharacter::TryInteract()
{
    FVector Start; FRotator Rotation; Controller->GetPlayerViewPoint(Start, Rotation); FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(RLSInteract), false, this);
    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Rotation.Vector() * 350.0f, ECC_Visibility, Params) && Hit.GetActor() && Hit.GetActor()->Implements<URLSInteractable>()) ServerInteract(Hit.GetActor());
}
void ARLSCharacter::ServerInteract_Implementation(AActor* Target) { if (IsValid(Target) && Target->GetClass()->ImplementsInterface(URLSInteractable::StaticClass())) IRLSInteractable::Execute_Interact(Target, this); }
void ARLSCharacter::UseFood() { ServerUseFood(); }
void ARLSCharacter::ServerUseFood_Implementation() { if (Inventory->RemoveItem(TEXT("Food"), 1)) { Survival->RestoreHunger(25); Survival->RestoreThirst(5); } }
void ARLSCharacter::CraftPlank() { ServerCraftPlank(); }
void ARLSCharacter::ServerCraftPlank_Implementation() { Crafting->Craft(TEXT("Plank")); }
void ARLSCharacter::BuildAtLookTarget()
{
    FVector Start; FRotator Rotation; Controller->GetPlayerViewPoint(Start, Rotation); FHitResult Hit; FCollisionQueryParams Params(SCENE_QUERY_STAT(RLSBuild), false, this);
    const FVector Location = GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Rotation.Vector() * 500.0f, ECC_Visibility, Params) ? Hit.ImpactPoint : Start + Rotation.Vector() * 250.0f;
    ServerBuild(FTransform(FRotator(0, Rotation.Yaw, 0), Location));
}
void ARLSCharacter::ServerBuild_Implementation(const FTransform& Transform) { if (FVector::DistSquared(GetActorLocation(), Transform.GetLocation()) <= FMath::Square(600.0f)) Building->PlaceDefaultBuilding(Transform); }
bool ARLSCharacter::SpendMoney(int32 Amount) { if (!HasAuthority() || Amount < 0 || Money < Amount) return false; Money -= Amount; return true; }
void ARLSCharacter::AddMoney(int32 Amount) { if (HasAuthority() && Amount > 0) Money += Amount; }
void ARLSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const { Super::GetLifetimeReplicatedProps(Out); DOREPLIFETIME(ARLSCharacter, Money); }
