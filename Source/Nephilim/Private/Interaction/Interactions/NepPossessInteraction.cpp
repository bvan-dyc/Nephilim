#include "Interaction/Interactions/NepPossessInteraction.h"
#include "Interaction/Resource/NepInteractionEvents.h"

void FNepPossessInteraction::ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.PossessCommands.Emplace(InteractingEntity, InteractableEntity);
}
