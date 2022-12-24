#pragma once

#include "CoreMinimal.h"
#include "NepLongInteractionProxy.h"
#include "NepInventoryInteractionProxy.generated.h"

UCLASS()
class ANepInventoryInteractionProxy : public ANepLongInteractionProxy
{
	GENERATED_BODY()

public:

	virtual bool EvaluateLongInteractionConditionsOnServer(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const override;

	virtual void OnLongInteractionStartedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;
	virtual void OnLongInteractionEndedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;

};
