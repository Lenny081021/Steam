#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "RLSGameUserSettings.generated.h"

UCLASS(Config=GameUserSettings)
class REALLIFESURVIVAL_API URLSGameUserSettings : public UGameUserSettings
{
    GENERATED_BODY()
public:
    UPROPERTY(Config, BlueprintReadWrite, Category="RLS Graphics") float FieldOfView = 90.0f;
    UPROPERTY(Config, BlueprintReadWrite, Category="RLS Graphics") float Brightness = 1.0f;
    UPROPERTY(Config, BlueprintReadWrite, Category="RLS Graphics") bool bUseLumen = true;
    UFUNCTION(BlueprintCallable, Category="RLS Graphics") void ApplyRLSSettings();
    UFUNCTION(BlueprintCallable, Category="RLS Graphics") static URLSGameUserSettings* GetRLSSettings();
};
