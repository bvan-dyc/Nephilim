#include "Interaction/Actor/NepLongInteractionProxy.h"
#include "ArcECSSubsystem.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Component/NepInteractor.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Net/UnrealNetwork.h"
#include "Resource/ArcCoreData.h"

ANepLongInteractionProxy::ANepLongInteractionProxy()
{
	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

void ANepLongInteractionProxy::InitializeProxy(AActor& InInteractorActor, AActor& InInteractableActor, int32 InInteractionIndex)
{
	InteractorActor = &InInteractorActor;
	InteractableActor = &InInteractableActor;
	InteractionIndex = InInteractionIndex;
}

void ANepLongInteractionProxy::TornOff()
{
	Super::TornOff();
	
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	FNepInteractionEvents* Events = Universe ? Universe->GetResource<FNepInteractionEvents>() : nullptr;
	if (Events)
	{
		Events->LongInteractionsToEndOnClient.Add(this);
	}
}

void ANepLongInteractionProxy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANepLongInteractionProxy, InteractorActor);
	DOREPLIFETIME(ANepLongInteractionProxy, InteractableActor);
}

void ANepLongInteractionProxy::Server_EndLongInteraction_Implementation()
{
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	if (FNepInteractionEvents* Events = Universe ? Universe->GetResource<FNepInteractionEvents>() : nullptr)
	{
		Events->LongInteractionsToEndOnServer.Add(this);
	}
}

FNepInteraction* ANepLongInteractionProxy::GetInteraction() const
{
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	FArcCoreData* CoreData = Universe ? Universe->GetResource<FArcCoreData>() : nullptr;
	FArcEntityHandle* InteractableEntity = CoreData && InteractableActor ? CoreData->EntitiesByActor.Find(InteractableActor) : nullptr;
	FNepInteractable* Interactable = InteractableEntity ? Universe->GetComponent<FNepInteractable>(*InteractableEntity) : nullptr;
	return Interactable && Interactable->Interactions.IsValidIndex(InteractionIndex) ? Interactable->Interactions[InteractionIndex].Get() : nullptr;
}

void ANepLongInteractionProxy::OnRep_Init()
{
	if (!InteractorActor || !InteractableActor) { return; }
	
	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(this);
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	if (!Universe) { return; }
	
	FArcEntityHandle* InteractorEntity = ECSSubsystem->FindEntityForActor(*InteractorActor);
	FNepInteractor* Interactor = InteractorEntity ? Universe->GetComponent<FNepInteractor>(*InteractorEntity) : nullptr;

	ANepLongInteractionProxy* ClientOnlyProxy = nullptr;
	for (int32 i = 0; i < Interactor->InteractionProxies.Num(); ++i)
	{
		ANepLongInteractionProxy* Proxy = Interactor->InteractionProxies[i].Get();
		if (Proxy && Proxy->StaticClass() == StaticClass())
		{
			ClientOnlyProxy = Proxy;
			Interactor->InteractionProxies.RemoveAtSwap(i);
			break;
		}
	}
	Interactor->InteractionProxies.Add(this);

	if (ClientOnlyProxy)
	{
		InteractionIndex = ClientOnlyProxy->InteractionIndex;
		OnReplacedByServer(ClientOnlyProxy);
		ClientOnlyProxy->Destroy();
	}
}
