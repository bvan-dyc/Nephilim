#include "Interaction/System/NepInteractionSystems.h"
#include "CollisionQueryParams.h"
#include "CollisionShape.h"
#include "Character/Actor/NepCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/Actor/NepLongInteractionProxy.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Component/NepInteractor.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "UI/Widget/NepHUDWidget.h"
#include "UI/Widget/NepInteractionMenuWidget.h"

void FNepInteractionSystems::DetectInteractable(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
	FArcRes<FNepInteractionEvents> Events)
{
	FArcEntityHandle InteractorEntity;
	FArcEntityHandle BestInteractableEntity = FArcEntityHandle();
	const FNepInteractable* BestInteractable = nullptr;

	{
		UWorld* World = CoreData->World.Get();
		APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
		ACharacter* Character = PlayerController ? PlayerController->GetCharacter() : nullptr;
		if (Character)
		{
			FArcEntityHandle* CharacterEntity = CoreData->EntitiesByActor.Find(Character);
			if (!CharacterEntity) { return; }
			InteractorEntity = *CharacterEntity;
			
			FVector CameraLocation;
			FRotator Rotation;
			PlayerController->GetPlayerViewPoint(CameraLocation, Rotation);
			const FVector CameraDirection = Rotation.Vector();
			TArray<FOverlapResult> Overlaps;
			FCollisionShape Sphere = FCollisionShape::MakeSphere(200.0f);
			FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(Character);
			World->OverlapMultiByChannel(Overlaps, Character->GetActorLocation(), Character->GetActorQuat(), ECC_GameTraceChannel1, Sphere, Params);
			TOptional<float> MinDot;

			for (const FOverlapResult& Overlap : Overlaps)
			{
				AActor* Actor = Overlap.GetActor();
				const FArcEntityHandle* Entity = CoreData->EntitiesByActor.Find(Overlap.GetActor());
				if (const FNepInteractable* Interactable = Entity ? Universe.GetComponent<FNepInteractable>(*Entity) : nullptr)
				{
					const float Dot = FVector::DotProduct(CameraDirection, (Actor->GetActorLocation() - Character->GetActorLocation()).GetSafeNormal());
					if (Dot > 0.5f && (!MinDot || Dot > *MinDot))
					{
						MinDot = Dot;
						BestInteractableEntity = *Entity;
						BestInteractable = Interactable;
					}
				}
			}
		}
	}

	if (CurrentInteractableData->FocusedInteractable != BestInteractableEntity)
	{
		Events->bUpdateInteractionMenu = true;
		Events->bCollapseInteractionMenu = true;
		CurrentInteractableData->FocusedInteractable = BestInteractableEntity;
		CurrentInteractableData->InteractionAvailabilities.Reset();
		CurrentInteractableData->NumAvailableInteractions = 0;
		if (BestInteractable)
		{
			CurrentInteractableData->InteractionAvailabilities.AddUninitialized(BestInteractable->Interactions.Num());
		}
	}

	if (BestInteractable && ensure(CurrentInteractableData->InteractionAvailabilities.Num() == BestInteractable->Interactions.Num()))
	{
		CurrentInteractableData->NumAvailableInteractions = 0;
		for (int32 i = 0; i < BestInteractable->Interactions.Num(); ++i)
		{
			const TUniquePtr<FNepInteraction>& Interaction = BestInteractable->Interactions[i];
			
			const bool bIsInteractionAvailable =
				Interaction->IsInteractionPossibleOnClient(Universe, InteractorEntity, BestInteractableEntity) &&
				(!Interaction->RequiresAttention() || !FNepInteractor::IsAttentionOccupied(Universe, InteractorEntity)) &&
				(!Interaction->RequiresBody() || !FNepInteractor::IsBodyOccupied(Universe, InteractorEntity));
			if (bIsInteractionAvailable) { ++CurrentInteractableData->NumAvailableInteractions; }
			
			if (CurrentInteractableData->InteractionAvailabilities[i] != bIsInteractionAvailable)
			{
				CurrentInteractableData->InteractionAvailabilities[i] = bIsInteractionAvailable;
				Events->bUpdateInteractionMenu = true;
			}
		}
	}
}

void FNepInteractionSystems::UpdateInteractionMenu(
	FArcUniverse& Universe,
	FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
	FArcRes<FNepInteractionEvents> Events,
	FArcRes<FNepWidgetData> WidgetData)
{
	if (!WidgetData->InteractionMenuWidget.IsValid()) { return; }

	if (Events->bUpdateInteractionMenu)
	{
		if (FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(CurrentInteractableData->FocusedInteractable))
		{
			TArray<FText> InteractionNames;
			for (TUniquePtr<FNepInteraction>& Interaction : Interactable->Interactions)
			{
				InteractionNames.Add(Interaction->GetInteractionName());
			}
			WidgetData->InteractionMenuWidget->ShowMainEntry();
			WidgetData->InteractionMenuWidget->SetEntries(InteractionNames);
		}
		else
		{
			WidgetData->InteractionMenuWidget->HideMainEntry();
		}
	}

	if (Events->bCollapseInteractionMenu)
	{
		WidgetData->InteractionMenuWidget->CollapseMenu();
	}
}

void FNepInteractionSystems::TriggerInteraction(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
	FArcRes<FNepInteractionEvents> Events,
	FArcRes<FNepWidgetData> WidgetData)
{
	TOptional<int32> InteractionToExecute;
	
	if (Events->bInteractionKeyPressed && Universe.IsValid(CurrentInteractableData->FocusedInteractable))
	{
		if (CurrentInteractableData->NumAvailableInteractions == 1)
		{
			InteractionToExecute = 0;
		}
		else if (CurrentInteractableData->NumAvailableInteractions > 1)
		{
			if (WidgetData->InteractionMenuWidget.IsValid())
			{
				WidgetData->InteractionMenuWidget->ToggleMenu();
			}
		}
	}

	if (Events->SelectedInteractionIndex && WidgetData->InteractionMenuWidget.IsValid() && WidgetData->InteractionMenuWidget->IsExpanded())
	{
		InteractionToExecute = *Events->SelectedInteractionIndex;
	}

	if (InteractionToExecute)
	{
		FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(CurrentInteractableData->FocusedInteractable);
		AActor* InteractableActor = Interactable ? Interactable->Actor.Get() : nullptr;
		if (InteractableActor && Interactable->Interactions.Num() == CurrentInteractableData->InteractionAvailabilities.Num())
		{
			int32 InteractionIndex = [&]
			{
				int32 AvailableAccumulator = 0;
				for (int32 i = 0; i < Interactable->Interactions.Num(); ++i)
				{
					if (CurrentInteractableData->InteractionAvailabilities[i])
					{
						if (AvailableAccumulator == *InteractionToExecute)
						{
							return i;
						}
						++AvailableAccumulator;
					}
				}
				return -1;
			}();
			if (FNepInteraction* Interaction = Interactable->Interactions.IsValidIndex(InteractionIndex) ? Interactable->Interactions[InteractionIndex].Get() : nullptr)
			{
				UWorld* World = CoreData->World.Get();
				APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
				ANepCharacter* Character = PlayerController ? Cast<ANepCharacter>(PlayerController->GetCharacter()) : nullptr;
				FArcEntityHandle* InteractingEntity = Character ? CoreData->EntitiesByActor.Find(Character) : nullptr;
				FNepInteractor* Interactor = InteractingEntity ? Universe.GetComponent<FNepInteractor>(*InteractingEntity) : nullptr;

				if (Interactor && InteractingEntity)
				{
					if (TSubclassOf<ANepLongInteractionProxy> ProxyClass = Interaction->GetLongInteractionProxyClass())
					{
						ANepLongInteractionProxy* Proxy = World->SpawnActor<ANepLongInteractionProxy>(ProxyClass);
						Proxy->InitializeProxy(*Character, *InteractableActor, InteractionIndex);
						Proxy->OnLongInteractionStartedOnClient(*InteractingEntity, CurrentInteractableData->FocusedInteractable, *Events);
						Interactor->InteractionProxies.Add(Proxy);
						if (Interaction->RequiresAttention())
						{
							Interactor->bIsAttentionOccupied = true;
						}
						if (Interaction->RequiresBody())
						{
							Interactor->bIsBodyOccupied = true;
						}
					}
					Interaction->ExecuteOnClient(*InteractingEntity, CurrentInteractableData->FocusedInteractable, *Events);
					if (Interaction->ShouldExecuteOnServer())
					{
						Character->Server_Interact(InteractableActor, InteractionIndex);
					}
				}
			}
		}
	}
}

void FNepInteractionSystems::EvaluateLongInteractionConditionsOnClient(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepInteractionEvents> Events)
{
	UWorld* World = CoreData->World.Get();
	APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
	ANepCharacter* Character = PlayerController ? Cast<ANepCharacter>(PlayerController->GetCharacter()) : nullptr;
	FArcEntityHandle* InteractingEntity = Character ? CoreData->EntitiesByActor.Find(Character) : nullptr;
	
	if (FNepInteractor* Interactor = InteractingEntity ? Universe.GetComponent<FNepInteractor>(*InteractingEntity) : nullptr)
	{
		for (TWeakObjectPtr<ANepLongInteractionProxy>& ProxyWeak : Interactor->InteractionProxies)
		{
			ANepLongInteractionProxy* Proxy = ProxyWeak.Get();
			AActor* InteractableActor = Proxy ? Proxy->InteractableActor.Get() : nullptr;
			if (FArcEntityHandle* InteractableEntity = InteractableActor ? CoreData->EntitiesByActor.Find(InteractableActor) : nullptr)
			{
				if (!Proxy->EvaluateLongInteractionConditionsOnClient(Universe, *InteractingEntity, *InteractableEntity))
				{
					Proxy->Server_EndLongInteraction();
					Events->LongInteractionsToEndOnClient.Add(Proxy);
				}
			}
		}
	}
}

void FNepInteractionSystems::EndLongInteractionsOnClient(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepInteractionEvents> Events)
{
	for (TWeakObjectPtr<ANepLongInteractionProxy>& ProxyWeak : Events->LongInteractionsToEndOnClient)
	{
		ANepLongInteractionProxy* Proxy = ProxyWeak.Get();
		if (!Proxy) { return; }
		FArcEntityHandle* InteractorEntity = CoreData->EntitiesByActor.Find(Proxy->InteractorActor.Get());
		FArcEntityHandle* InteractableEntity = CoreData->EntitiesByActor.Find(Proxy->InteractableActor.Get());
		if (InteractorEntity && InteractableEntity)
		{
			Proxy->OnLongInteractionEndedOnClient(*InteractorEntity, *InteractableEntity, *Events);
			
			FNepInteraction* Interaction = Proxy->GetInteraction();
			FNepInteractor* Interactor = Universe.GetComponent<FNepInteractor>(*InteractorEntity);
			if (Interaction && Interactor)
			{
				if (Interaction->RequiresAttention())
				{
					Interactor->bIsAttentionOccupied = false;
				}
				if (Interaction->RequiresBody())
				{
					Interactor->bIsBodyOccupied = false;
				}
			}
		}
	}
}

void FNepInteractionSystems::CleanUpLongInteractionsOnClient(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepInteractionEvents> Events)
{
	for (TWeakObjectPtr<ANepLongInteractionProxy>& ProxyWeak : Events->LongInteractionsToEndOnClient)
	{
		ANepLongInteractionProxy* Proxy = ProxyWeak.Get();
		if (!Proxy) { return; }
		FArcEntityHandle* InteractorEntity = CoreData->EntitiesByActor.Find(Proxy->InteractorActor.Get());
		if (FNepInteractor* Interactor = InteractorEntity ? Universe.GetComponent<FNepInteractor>(*InteractorEntity) : nullptr)
		{
			Interactor->InteractionProxies.RemoveSingleSwap(Proxy);
		}
		// TODO: Remove proxies from the interactable in the future.
		// FArcEntityHandle* InteractableEntity = CoreData->EntitiesByActor.Find(Proxy->InteractableActor.Get());
		// if (FNepInteractable* Interactable = InteractableEntity ? Universe.GetComponent<FNepInteractable>(*InteractableEntity) : nullptr)
		// {
		// }
		Proxy->Destroy();
	}
}

void FNepInteractionSystems::EvaluateLongInteractionConditionsOnServer(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepServerInteractionData> ServerInteractionData,
	FArcRes<FNepInteractionEvents> Events)
{
	for (int32 i = ServerInteractionData->InteractionProxies.Num() - 1; i >= 0; --i)
	{
		ANepLongInteractionProxy* Proxy = ServerInteractionData->InteractionProxies[i].Get();
		if (!ensure(Proxy))
		{
			ServerInteractionData->InteractionProxies.RemoveAtSwap(i);
			continue;
		}
		
		const bool bEndInteraction = [&]
		{
			if (!Proxy->InteractorActor || !Proxy->InteractableActor) { return true; }
			FArcEntityHandle* InteractorEntity = CoreData->EntitiesByActor.Find(Proxy->InteractorActor.Get());
			FArcEntityHandle* InteractableEntity = CoreData->EntitiesByActor.Find(Proxy->InteractableActor.Get());
			if (!InteractorEntity || !InteractableEntity) { return true; }
			
			return !Proxy->EvaluateLongInteractionConditionsOnServer(Universe, *InteractorEntity, *InteractableEntity);
		}();

		if (bEndInteraction)
		{
			Events->LongInteractionsToEndOnServer.Add(Proxy);
		}
	}
}

void FNepInteractionSystems::EndLongInteractionsOnServer(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepInteractionEvents> Events)
{
	for (TWeakObjectPtr<ANepLongInteractionProxy>& ProxyWeak : Events->LongInteractionsToEndOnServer)
	{
		ANepLongInteractionProxy* Proxy = ProxyWeak.Get();
		if (!Proxy) { return; }
		FArcEntityHandle* InteractorEntity = CoreData->EntitiesByActor.Find(Proxy->InteractorActor.Get());
		FArcEntityHandle* InteractableEntity = CoreData->EntitiesByActor.Find(Proxy->InteractableActor.Get());
		if (InteractorEntity && InteractableEntity)
		{
			Proxy->OnLongInteractionEndedOnServer(*InteractorEntity, *InteractableEntity, *Events);
			
			FNepInteraction* Interaction = Proxy->GetInteraction();
			FNepInteractor* Interactor = Universe.GetComponent<FNepInteractor>(*InteractableEntity);
			if (Interaction && Interactor)
			{
				if (Interaction->RequiresAttention())
				{
					Interactor->bIsAttentionOccupied = false;
				}
				if (Interaction->RequiresBody())
				{
					Interactor->bIsBodyOccupied = false;
				}
			}
		}
	}
}

void FNepInteractionSystems::CleanUpLongInteractionsOnServer(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepServerInteractionData> ServerInteractionData,
	FArcRes<FNepInteractionEvents> Events)
{
	for (TWeakObjectPtr<ANepLongInteractionProxy>& ProxyWeak : Events->LongInteractionsToEndOnServer)
	{
		ANepLongInteractionProxy* Proxy = ProxyWeak.Get();
		if (!Proxy) { return; }
		FArcEntityHandle* InteractorEntity = CoreData->EntitiesByActor.Find(Proxy->InteractorActor.Get());
		if (FNepInteractor* Interactor = InteractorEntity ? Universe.GetComponent<FNepInteractor>(*InteractorEntity) : nullptr)
		{
			Interactor->InteractionProxies.RemoveSingleSwap(Proxy);
		}
		// TODO: Remove proxies from the interactable in the future.
		// FArcEntityHandle* InteractableEntity = CoreData->EntitiesByActor.Find(Proxy->InteractableActor.Get());
		// if (FNepInteractable* Interactable = InteractableEntity ? Universe.GetComponent<FNepInteractable>(*InteractableEntity) : nullptr)
		// {
		// }
		ServerInteractionData->InteractionProxies.RemoveSingleSwap(Proxy);
		Proxy->TearOff();

		// Very hacky, but for some reason TornOff won't be called on the Proxy if it is destroyed immediately.
		Proxy->ForceNetUpdate();
		if (UWorld* World = Proxy->GetWorld())
		{
			FTimerHandle TimerHandle;
			FTimerDelegate DestroyDelegate = FTimerDelegate::CreateWeakLambda(Proxy, [&](AActor* ActorToDestroy)
			{
				ActorToDestroy->Destroy();
			}, Proxy);
			World->GetTimerManager().SetTimer(TimerHandle, DestroyDelegate, 10.0f, false);
		}
	}
}

void FNepInteractionSystems::UpdateInteractableIndicator(FArcRes<FNepWidgetData> WidgetData)
{
	if (WidgetData->HUDWidget.IsValid())
	{
		WidgetData->HUDWidget->UpdateInteractableIndicator();
	}
}

void FNepInteractionSystems::ClearEvents(FArcRes<FNepInteractionEvents> Events)
{
	*Events = FNepInteractionEvents();
}
