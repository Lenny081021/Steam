#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RLSPlayerController.generated.h"

class URLSMainMenuWidget;
UCLASS()
class REALLIFESURVIVAL_API ARLSPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly, Category="UI") TSubclassOf<URLSMainMenuWidget> MainMenuClass;
};
