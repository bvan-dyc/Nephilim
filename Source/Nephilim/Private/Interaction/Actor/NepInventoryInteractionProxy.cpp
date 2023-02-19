#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Interaction/NepInteractionHelper.h"
#include "Interaction/Resource/NepInteractionEvents.h"

bool ANepInventoryInteractionProxy::EvaluateLongInteractionConditionsOnClient(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const
{
	const FNepCharacterEvents* Events = Universe.GetResource<FNepCharacterEvents>();
	if (Events && Events->SetUIVisibilityCommand.IsSet() && !(*Events->SetUIVisibilityCommand)) { return false; }
	return true;
}

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
