#include "Character/ActorComponent/NepPlayerInputComponent.h"
#include "ArcECSSubsystem.h"
#include "Interaction/Resource/NepInteractionEvents.h"

void UNepPlayerInputComponent::SetupBindings()
{
    BindAction(TEXT("PossessTarget"), IE_Pressed, this, &UNepPlayerInputComponent::PossessTarget);
}

void UNepPlayerInputComponent::PossessTarget()
{
	/*UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	if (FNepInteractionEvents* Events = Universe ? Universe->GetResource<FNepInteractionEvents>() : nullptr)
	{
		Events->bPossessTarget = true;
	}*/
}
