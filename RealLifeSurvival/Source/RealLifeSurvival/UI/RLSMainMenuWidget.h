#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RLSMainMenuWidget.generated.h"

class UButton;
UCLASS()
class REALLIFESURVIVAL_API URLSMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeConstruct() override;
private:
    UFUNCTION() void StartGame();
    UFUNCTION() void QuitGame();
    UButton* MakeButton(const FText& Label);
};
