#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Interaction/NepInteractionHelper.h"
#include "Interaction/Resource/NepInteractionEvents.h"

bool ANepInventoryInteractionProxy::EvaluateLongInteractionConditionsOnServer(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const
{
	return FNepInteractionHelper::IsInInteractionRange(Universe, InteractingEntity, InteractableEntity);
}

void ANepInventoryInteractionProxy::OnLongInteractionStartedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.ContainerToLoot = InteractableEntity;
}

void ANepInventoryInteractionProxy::OnLongInteractionEndedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.ContainerToStopLooting = InteractableEntity;
}
