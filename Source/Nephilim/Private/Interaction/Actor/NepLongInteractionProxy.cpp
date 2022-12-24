#include "Interaction/Actor/NepLongInteractionProxy.h"
#include "ArcECSSubsystem.h"
#include "Interaction/Component/NepInteractor.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Net/UnrealNetwork.h"
#include "Resource/ArcCoreData.h"

ANepLongInteractionProxy::ANepLongInteractionProxy()
{
	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

void ANepLongInteractionProxy::InitializeProxy(AActor& InInteractorActor, AActor& InInteractableActor)
{
	InteractorActor = &InInteractorActor;
	InteractableActor = &InInteractableActor;
}

void ANepLongInteractionProxy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsNetMode(ENetMode::NM_Client) && GetLocalRole() == ENetRole::ROLE_AutonomousProxy && !bHasInteractionEndedOnClient)
	{
		UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
		FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
		FArcCoreData* CoreData = Universe ? Universe->GetResource<FArcCoreData>() : nullptr;
		FNepInteractionEvents* Events = Universe ? Universe->GetResource<FNepInteractionEvents>() : nullptr;
		if (CoreData && Events)
		{
			FArcEntityHandle* InteractorEntity = InteractorActor ? CoreData->EntitiesByActor.Find(InteractableActor) : nullptr;
			FArcEntityHandle* InteractableEntity = InteractableActor ? CoreData->EntitiesByActor.Find(InteractableActor) : nullptr;
			if (InteractorEntity && InteractableEntity)
			{
				OnLongInteractionEndedOnClient(*InteractorEntity, *InteractableEntity, *Events);
			}
		}
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

void ANepLongInteractionProxy::OnRep_Init()
{
	if (!InteractorActor || !InteractableActor) { return; }
	
	UWorld* World = GetWorld();
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

	if (ClientOnlyProxy)
	{
		OnReplacedByServer(ClientOnlyProxy);
		ClientOnlyProxy->Destroy();
	}
}

