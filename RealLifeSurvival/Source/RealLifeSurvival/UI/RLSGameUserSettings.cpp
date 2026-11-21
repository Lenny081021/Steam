#include "UI/RLSGameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/Engine.h"

URLSGameUserSettings* URLSGameUserSettings::GetRLSSettings() { return Cast<URLSGameUserSettings>(UGameUserSettings::GetGameUserSettings()); }
void URLSGameUserSettings::ApplyRLSSettings()
{
    ApplySettings(false); SaveSettings();
    if (UWorld* World = GEngine ? GEngine->GetCurrentPlayWorld() : nullptr)
    {
        if (APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0)) if (PC->PlayerCameraManager) PC->PlayerCameraManager->SetFOV(FieldOfView);
    }
}
