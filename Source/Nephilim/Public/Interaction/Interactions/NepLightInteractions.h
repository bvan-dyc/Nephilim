#pragma once

#include "NepInteraction.h"

class FNepToggleLightInteraction : public FNepInteraction
{
public:
	virtual FText GetInteractionName() const override { return NSLOCTEXT("Interaction", "InteractionToggleLight", "Toggle"); }
	virtual bool ShouldExecuteOnServer() const override { return true; }
	virtual void ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;
};

class FNepRandomizeLightColorInteraction : public FNepInteraction
{
public:
	virtual FText GetInteractionName() const override { return NSLOCTEXT("Interaction", "InteractionRandomizeLightColor", "Randomize Color"); }
	virtual bool ShouldExecuteOnServer() const override { return true; }
	virtual void ExecuteOnServer(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;
};
