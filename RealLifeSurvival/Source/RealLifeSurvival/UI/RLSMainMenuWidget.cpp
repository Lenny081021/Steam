#include "UI/RLSMainMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

UButton* URLSMainMenuWidget::MakeButton(const FText& Label)
{
    UButton* Button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
    UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()); Text->SetText(Label); Text->SetJustification(ETextJustify::Center); Button->SetContent(Text); return Button;
}
void URLSMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (WidgetTree->RootWidget) return;
    UVerticalBox* Menu = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass()); WidgetTree->RootWidget = Menu;
    UTextBlock* Title = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()); Title->SetText(FText::FromString(TEXT("REAL LIFE SURVIVAL"))); Title->SetJustification(ETextJustify::Center); Menu->AddChildToVerticalBox(Title);
    UButton* Play = MakeButton(NSLOCTEXT("RLS", "Play", "SPIELEN")); Play->OnClicked.AddDynamic(this, &URLSMainMenuWidget::StartGame); Menu->AddChildToVerticalBox(Play);
    UButton* Quit = MakeButton(NSLOCTEXT("RLS", "Quit", "BEENDEN")); Quit->OnClicked.AddDynamic(this, &URLSMainMenuWidget::QuitGame); Menu->AddChildToVerticalBox(Quit);
}
void URLSMainMenuWidget::StartGame() { RemoveFromParent(); if (APlayerController* PC = GetOwningPlayer()) { FInputModeGameOnly Mode; PC->SetInputMode(Mode); PC->bShowMouseCursor = false; } }
void URLSMainMenuWidget::QuitGame() { UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false); }
