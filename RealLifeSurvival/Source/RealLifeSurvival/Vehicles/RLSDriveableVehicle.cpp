#include "Vehicles/RLSDriveableVehicle.h"
#include "Player/RLSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"

ARLSDriveableVehicle::ARLSDriveableVehicle()
{
    bReplicates = true; SetReplicateMovement(true); PrimaryActorTick.bCanEverTick = true;
    Chassis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chassis")); RootComponent = Chassis; Chassis->SetCollisionProfileName(TEXT("BlockAll"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube")); if (Cube.Succeeded()) Chassis->SetStaticMesh(Cube.Object); Chassis->SetRelativeScale3D(FVector(2.3f, 1.0f, .55f));
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); CameraBoom->SetupAttachment(Chassis); CameraBoom->TargetArmLength = 500.0f; CameraBoom->SetRelativeLocation(FVector(0,0,100)); CameraBoom->bUsePawnControlRotation = true;
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); Camera->SetupAttachment(CameraBoom); Camera->bUsePawnControlRotation = false;
}
void ARLSDriveableVehicle::SetupPlayerInputComponent(UInputComponent* Input)
{
    Input->BindAxis(TEXT("MoveForward"), this, &ARLSDriveableVehicle::SetThrottle); Input->BindAxis(TEXT("MoveRight"), this, &ARLSDriveableVehicle::SetSteering);
    Input->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput); Input->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    Input->BindAction(TEXT("Interact"), IE_Pressed, this, &ARLSDriveableVehicle::ExitVehicle); Input->BindAction(TEXT("Jump"), IE_Pressed, this, &ARLSDriveableVehicle::ToggleEngine);
}
void ARLSDriveableVehicle::Tick(float DeltaSeconds) { Super::Tick(DeltaSeconds); if (HasAuthority()) ApplyDriveInput(DeltaSeconds); }
void ARLSDriveableVehicle::ApplyDriveInput(float DeltaSeconds)
{
    if (!bEngineRunning || FuelLitres <= 0.0f) { SpeedKmh = FMath::FInterpTo(SpeedKmh, 0.0f, DeltaSeconds, 2.0f); return; }
    SpeedKmh = FMath::Clamp(SpeedKmh + ThrottleInput * 45.0f * DeltaSeconds, -20.0f, MaxSpeedKmh);
    if (FMath::IsNearlyZero(ThrottleInput)) SpeedKmh = FMath::FInterpTo(SpeedKmh, 0.0f, DeltaSeconds, .7f);
    AddActorWorldRotation(FRotator(0.0f, SteeringInput * FMath::Clamp(SpeedKmh / MaxSpeedKmh, -1.0f, 1.0f) * 75.0f * DeltaSeconds, 0.0f));
    AddActorWorldOffset(GetActorForwardVector() * (SpeedKmh / 3.6f) * 100.0f * DeltaSeconds, true);
    FuelLitres = FMath::Max(0.0f, FuelLitres - FMath::Abs(ThrottleInput) * .002f * DeltaSeconds);
}
void ARLSDriveableVehicle::SetThrottle(float Value) { ServerSetDrive(Value, SteeringInput); }
void ARLSDriveableVehicle::SetSteering(float Value) { ServerSetDrive(ThrottleInput, Value); }
void ARLSDriveableVehicle::ServerSetDrive_Implementation(float NewThrottle, float NewSteering) { if (Driver && GetController() && GetController()->GetPawn() == this) { ThrottleInput=FMath::Clamp(NewThrottle,-1.0f,1.0f); SteeringInput=FMath::Clamp(NewSteering,-1.0f,1.0f); } }
void ARLSDriveableVehicle::ToggleEngine() { if (HasAuthority() && Driver) bEngineRunning = !bEngineRunning; }
void ARLSDriveableVehicle::Interact_Implementation(AActor* InteractingActor) { if (ARLSCharacter* Character = Cast<ARLSCharacter>(InteractingActor)) ServerEnter(Character); }
FText ARLSDriveableVehicle::GetInteractionText_Implementation() const { return NSLOCTEXT("RLS", "EnterCar", "Fahrzeug benutzen"); }
void ARLSDriveableVehicle::ServerEnter_Implementation(ARLSCharacter* Character)
{
    if (!Character || Driver || FVector::DistSquared(Character->GetActorLocation(), GetActorLocation()) > FMath::Square(400.0f)) return;
    AController* Controller = Character->GetController(); if (!Controller) return; Driver=Character; Character->SetActorHiddenInGame(true); Character->SetActorEnableCollision(false); Controller->Possess(this); bEngineRunning=true;
}
void ARLSDriveableVehicle::ExitVehicle() { ServerExit(); }
void ARLSDriveableVehicle::ServerExit_Implementation()
{
    if (!Driver || !GetController()) return; ARLSCharacter* Character = Driver; AController* Controller = GetController();
    Character->SetActorLocation(GetActorLocation() + GetActorRightVector() * 180.0f + FVector(0,0,100)); Character->SetActorHiddenInGame(false); Character->SetActorEnableCollision(true); Driver=nullptr; bEngineRunning=false; Controller->Possess(Character);
}
void ARLSDriveableVehicle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const { Super::GetLifetimeReplicatedProps(Out); DOREPLIFETIME(ARLSDriveableVehicle, FuelLitres); DOREPLIFETIME(ARLSDriveableVehicle, SpeedKmh); DOREPLIFETIME(ARLSDriveableVehicle, bEngineRunning); DOREPLIFETIME(ARLSDriveableVehicle, Driver); }
