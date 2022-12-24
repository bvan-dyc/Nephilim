#pragma once

#include "NepInteraction.h"

class FNepLootInteraction : public FNepInteraction
{
public:
	virtual FText GetInteractionName() const override { return NSLOCTEXT("Interaction", "InteractionLoot", "Loot"); }
	virtual bool ShouldExecuteOnServer() const override { return true; }

	virtual TSubclassOf<class ANepLongInteractionProxy> GetLongInteractionProxyClass() override;
};
