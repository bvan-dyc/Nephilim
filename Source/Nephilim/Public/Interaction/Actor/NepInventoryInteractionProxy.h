#pragma once

#include "CoreMinimal.h"
#include "NepLongInteractionProxy.h"
#include "Inventory/NepItemID.h"
#include "NepInventoryInteractionProxy.generated.h"

USTRUCT()
struct FNepMoveItemInventoryCommand
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FNepItemID ItemID;

	UPROPERTY()
	bool bToTarget;

public:

	void Send(class ANepInventoryInteractionProxy& Proxy) const;
};

class FNepInventoryCommandBase
{
public:
	
	virtual ~FNepInventoryCommandBase() {}
	
	virtual void Send(class ANepInventoryInteractionProxy& Proxy) const {}
};

template<typename T>
class FNepInventoryCommandWrapper : public FNepInventoryCommandBase
{
public:
	
	T InventoryCommand;

public:
	
	FNepInventoryCommandWrapper(T&& Command) : InventoryCommand(Command) {}

	virtual void Send(class ANepInventoryInteractionProxy& Proxy) const override
	{
		InventoryCommand.Send(Proxy);
	}
};

UCLASS()
class ANepInventoryInteractionProxy : public ANepLongInteractionProxy
{
	GENERATED_BODY()

private:

	TArray<TSharedPtr<FNepInventoryCommandBase>> CommandBuffer;
	int32 NumSent = 0;

public:

	virtual bool EvaluateLongInteractionConditionsOnClient(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const override;
	virtual bool EvaluateLongInteractionConditionsOnServer(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const override;

	virtual void OnLongInteractionStartedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;
	virtual void OnLongInteractionEndedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const override;

	void MoveItem(const FNepItemID& ItemID, bool bMoveToInteractable);
	
	UFUNCTION(Server, Reliable)
	void Server_MoveItem(FNepItemID ItemID, bool bMoveToInteractable);

protected:
	
	virtual void OnReplacedByServer(ANepLongInteractionProxy* ClientOnlyProxy) override;

private:

	void SendPendingCommands();

	bool CanMoveItem(const struct FNepItemID& ItemID, bool bMoveToInteractable) const;

};
