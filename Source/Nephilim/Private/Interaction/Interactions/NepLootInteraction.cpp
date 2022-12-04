#include "Interaction/Interactions/NepLootInteraction.h"
#include "Interaction/Resource/NepInteractionEvents.h"

void FNepLootInteraction::ExecuteOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.bLootTarget = true;
}
