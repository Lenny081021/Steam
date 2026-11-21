#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "World/RLSInteractable.h"
#include "RLSDriveableVehicle.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class ARLSCharacter;

/** A dependency-free, drivable prototype car. Replace its movement implementation
 * with ChaosWheeledVehicleMovement after a skeletal chassis and wheel assets exist. */
UCLASS()
class REALLIFESURVIVAL_API ARLSDriveableVehicle : public APawn, public IRLSInteractable
{
    GENERATED_BODY()
public:
    ARLSDriveableVehicle();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Interact_Implementation(AActor* InteractingActor) override;
    virtual FText GetInteractionText_Implementation() const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UStaticMeshComponent> Chassis;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UCameraComponent> Camera;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Vehicle") float FuelLitres = 35.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle") float FuelCapacity = 45.0f;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Vehicle") float SpeedKmh = 0.0f;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Vehicle") bool bEngineRunning = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle") float MaxSpeedKmh = 90.0f;

    UFUNCTION(BlueprintCallable, Category="Vehicle") void ExitVehicle();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
    void SetThrottle(float Value);
    void SetSteering(float Value);
    void ToggleEngine();
    void ApplyDriveInput(float DeltaSeconds);
    UFUNCTION(Server, Reliable) void ServerEnter(ARLSCharacter* Character);
    UFUNCTION(Server, Reliable) void ServerExit();
    UFUNCTION(Server, Reliable) void ServerSetDrive(float NewThrottle, float NewSteering);
    UPROPERTY(Replicated) TObjectPtr<ARLSCharacter> Driver;
    float ThrottleInput = 0.0f;
    float SteeringInput = 0.0f;
};
