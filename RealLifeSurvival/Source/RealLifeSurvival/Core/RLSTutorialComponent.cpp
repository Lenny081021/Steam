#include "Core/RLSTutorialComponent.h"
#include "Player/RLSCharacter.h"
#include "Net/UnrealNetwork.h"

URLSTutorialComponent::URLSTutorialComponent() { SetIsReplicatedByDefault(true); }
bool URLSTutorialComponent::AdvanceTo(ERLSTutorialStep ReachedStep)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || CurrentStep == ERLSTutorialStep::Complete || uint8(ReachedStep) != uint8(CurrentStep) + 1) return false;
    CurrentStep = ReachedStep;
    if (CurrentStep == ERLSTutorialStep::DeliverPackage) { CurrentStep = ERLSTutorialStep::Complete; if (ARLSCharacter* Player = Cast<ARLSCharacter>(GetOwner())) Player->AddMoney(500); }
    return true;
}
FText URLSTutorialComponent::GetObjectiveText() const
{
    switch (CurrentStep) { case ERLSTutorialStep::LeaveApartment: return NSLOCTEXT("RLS","T1","Verlasse die Wohnung und gehe zum Supermarkt."); case ERLSTutorialStep::VisitSupermarket: return NSLOCTEXT("RLS","T2","Sprich am Supermarkt mit dem Auftraggeber."); case ERLSTutorialStep::MeetClient: return NSLOCTEXT("RLS","T3","Hole das Lieferfahrzeug am Autohaus ab."); case ERLSTutorialStep::CollectVehicle: return NSLOCTEXT("RLS","T4","Fahre zum Lieferziel."); case ERLSTutorialStep::DeliverPackage: return NSLOCTEXT("RLS","T5","Lieferung abgeschlossen."); default: return NSLOCTEXT("RLS","TDone","Tutorial abgeschlossen: 500 € erhalten."); }
}
void URLSTutorialComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const { Super::GetLifetimeReplicatedProps(Out); DOREPLIFETIME(URLSTutorialComponent, CurrentStep); }
