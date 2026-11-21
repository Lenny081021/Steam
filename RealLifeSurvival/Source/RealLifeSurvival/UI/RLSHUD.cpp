#include "UI/RLSHUD.h"
#include "Player/RLSCharacter.h"
#include "Survival/RLSSurvivalComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"

void ARLSHUD::DrawHUD()
{
    Super::DrawHUD();
    ARLSCharacter* Player = Cast<ARLSCharacter>(GetOwningPawn()); if (!Player || !Canvas || !GEngine) return;
    const URLSSurvivalComponent* S = Player->Survival;
    const FString Stats = FString::Printf(TEXT("GES %3.0f  HUN %3.0f  DUR %3.0f  AUS %3.0f   € %d"), S->Health, S->Hunger, S->Thirst, S->Stamina, Player->Money);
    DrawText(Stats, FColor::White, 32.0f, 32.0f, GEngine->GetSmallFont(), 1.2f, false);
    DrawText(TEXT("WASD Bewegen | E Interagieren | C Perspektive | F Nahrung"), FColor(200,200,200), 32.0f, 58.0f, GEngine->GetSmallFont(), 0.9f, false);
}
