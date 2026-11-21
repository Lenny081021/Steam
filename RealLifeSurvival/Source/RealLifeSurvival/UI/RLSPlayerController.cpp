#include "UI/RLSPlayerController.h"
#include "UI/RLSMainMenuWidget.h"

void ARLSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (IsLocalController())
    {
        TSubclassOf<URLSMainMenuWidget> MenuClass = MainMenuClass ? MainMenuClass : URLSMainMenuWidget::StaticClass();
        if (URLSMainMenuWidget* Menu = CreateWidget<URLSMainMenuWidget>(this, MenuClass)) { Menu->AddToViewport(100); bShowMouseCursor = true; FInputModeUIOnly Mode; Mode.SetWidgetToFocus(Menu->TakeWidget()); SetInputMode(Mode); }
    }
}
