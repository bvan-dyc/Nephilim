#pragma once

class FNepInteraction
{
public:
	virtual ~FNepInteraction() {}
	
	virtual FText GetInteractionName() const { return FText(); }

	virtual bool ShouldExecuteOnServer() const { return false; }

	virtual bool IsInteractionPossibleOnClient(const class FArcUniverse& Universe, class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity) const { return true; }
	virtual bool IsInteractionPossibleOnServer(const class FArcUniverse& Universe, class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity) const { return true; }

	virtual void ExecuteOnClient(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
	virtual void ExecuteOnServer(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}

	virtual bool RequiresAttention() const { return false; }
	virtual bool RequiresBody() const { return false; }

	virtual TSubclassOf<class ANepLongInteractionProxy> GetLongInteractionProxyClass() { return nullptr; }

};
