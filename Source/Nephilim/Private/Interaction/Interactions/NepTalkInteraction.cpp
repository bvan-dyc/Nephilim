#include "Interaction/Interactions/NepTalkInteraction.h"
#include "Interaction/Resource/NepInteractionEvents.h"

void FNepTalkInteraction::ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.TalkCommands.Emplace(InteractingEntity, InteractableEntity);
}
