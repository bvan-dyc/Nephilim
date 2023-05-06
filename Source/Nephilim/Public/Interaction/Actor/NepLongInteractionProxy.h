#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NepLongInteractionProxy.generated.h"

/**
 * An interaction proxy is used to communicate with the server during ongoing interactions. As soon as the interaction
 * begins an instance will be spawned on the client. It will be replaced by another instance that was spawned on the
 * server once it has been replicated to the client. The client-only instance can't do server RPCs, but it can be used
 * to buffer certain commands so that they can be send to the server as soon as the instance has been replaced.
 */
UCLASS()
class ANepLongInteractionProxy : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(ReplicatedUsing = "OnRep_Init")
	TObjectPtr<AActor> InteractorActor;

	UPROPERTY(ReplicatedUsing = "OnRep_Init")
	TObjectPtr<AActor> InteractableActor;

	UPROPERTY(ReplicatedUsing = "OnRep_Init")
	int32 InteractionIndex = INDEX_NONE;

	bool bHasInteractionEndedOnClient = false;

public:

	ANepLongInteractionProxy();

	void InitializeProxy(AActor& InInteractorActor, AActor& InInteractableActor, int32 InInteractionIndex);

	virtual void TornOff() override;
	
	virtual bool EvaluateLongInteractionConditionsOnClient(
		const class FArcUniverse& Universe,
		class FArcEntityHandle& InteractingEntity,
		class FArcEntityHandle& InteractableEntity) const { return true; }
	
	virtual bool EvaluateLongInteractionConditionsOnServer(
		const class FArcUniverse& Universe,
		class FArcEntityHandle& InteractingEntity,
		class FArcEntityHandle& InteractableEntity) const { return true; }

	virtual void OnLongInteractionStartedOnClient(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
	virtual void OnLongInteractionEndedOnClient(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
	
	virtual void OnLongInteractionStartedOnServer(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
	virtual void OnLongInteractionEndedOnServer(class FArcEntityHandle& InteractingEntity, class FArcEntityHandle& InteractableEntity, struct FNepInteractionEvents& Events) const {}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void EndLongInteractionOnClient();
	
	class FNepInteraction* GetInteraction() const;

protected:
	
	UFUNCTION(Server, Reliable)
	void Server_EndLongInteraction();

	virtual void OnReplacedByServer(ANepLongInteractionProxy* ClientOnlyProxy) {}
	bool IsClientOnlyProxy() const;

private:

	UFUNCTION()
	void OnRep_Init();
};
