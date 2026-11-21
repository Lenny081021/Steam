#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RLSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class URLSInventoryComponent;
class URLSSurvivalComponent;
class URLSCraftingComponent;
class URLSBuildingComponent;
class URLSQuestComponent;
class URLSTutorialComponent;

UCLASS()
class REALLIFESURVIVAL_API ARLSCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ARLSCharacter();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<UCameraComponent> FirstPersonCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<USpringArmComponent> ThirdPersonBoom;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<UCameraComponent> ThirdPersonCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components") TObjectPtr<URLSInventoryComponent> Inventory;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components") TObjectPtr<URLSSurvivalComponent> Survival;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components") TObjectPtr<URLSCraftingComponent> Crafting;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components") TObjectPtr<URLSBuildingComponent> Building;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components") TObjectPtr<URLSQuestComponent> Quests;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Economy") int32 Money = 2500;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components") TObjectPtr<URLSTutorialComponent> Tutorial;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="Player") void TogglePerspective();
    UFUNCTION(BlueprintCallable, Category="Player") void TryInteract();
    UFUNCTION(BlueprintCallable, Category="Player") bool SpendMoney(int32 Amount);
    UFUNCTION(BlueprintCallable, Category="Player") void AddMoney(int32 Amount);
    UFUNCTION(BlueprintPure, Category="Player") bool IsFirstPerson() const { return bFirstPerson; }
protected:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void BeginSprint();
    void EndSprint();
    void ToggleCrouch();
    void UseFood();
    void CraftPlank();
    void BuildAtLookTarget();
    UFUNCTION(Server, Reliable) void ServerInteract(AActor* Target);
    UFUNCTION(Server, Reliable) void ServerUseFood();
    UFUNCTION(Server, Reliable) void ServerCraftPlank();
    UFUNCTION(Server, Reliable) void ServerBuild(const FTransform& Transform);
    bool bFirstPerson = true;
    float WalkSpeed = 350.0f;
    float SprintSpeed = 650.0f;
};
