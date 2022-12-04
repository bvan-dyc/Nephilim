#pragma once

#include "NepInteraction.h"

class FNepPossessInteraction : public FNepInteraction
{
public:
	virtual FText GetInteractionName() const override { return NSLOCTEXT("Interaction", "InteractionPossess", "Possess"); }
	
	virtual bool ShouldExecuteOnServer() const override { return true; }
	
	virtual void ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;
	
};
