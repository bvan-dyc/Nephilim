#pragma once

class FNepInteraction
{
public:
	virtual ~FNepInteraction() {}
	
	virtual FText GetInteractionName() const { return FText(); }
	
	virtual bool ShouldExecuteOnServer() const { return false; }

	virtual bool IsInteractionPossibleOnClient() const { return true; }
	virtual bool IsInteractionPossibleOnServer() const { return true; }
	
	virtual void ExecuteOnClient(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
	virtual void ExecuteOnServer(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
};
