#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RLSHUD.generated.h"

UCLASS()
class REALLIFESURVIVAL_API ARLSHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void DrawHUD() override;
};
