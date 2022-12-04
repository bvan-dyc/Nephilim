#include "Interaction/Interactions/NepLightInteractions.h"
#include "Interaction/Resource/NepInteractionEvents.h"

void FNepToggleLightInteraction::ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.LightsToToggle.Add(InteractableEntity);
}

void FNepRandomizeLightColorInteraction::ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.LightsToRandomize.Add(InteractableEntity);
}
