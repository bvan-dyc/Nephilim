#pragma once

#include "NepInteraction.h"

class FNepLootInteraction : public FNepInteraction
{
public:
	virtual FText GetInteractionName() const override { return NSLOCTEXT("Interaction", "InteractionLoot", "Loot"); }
	virtual void ExecuteOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;
};
