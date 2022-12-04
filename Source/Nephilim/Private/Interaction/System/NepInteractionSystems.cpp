#include "Interaction/System/NepInteractionSystems.h"
#include "CollisionQueryParams.h"
#include "CollisionShape.h"
#include "Character/Actor/NepCharacter.h"
#include "Character/Actor/NepPlayerController.h"
#include "Character/Component/NepCharacterData.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/ActorComponent/NepInteractableLightComponent.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Item/Component/NepItemContainer.h"
#include "UI/Widget/NepHUDWidget.h"
#include "UI/Widget/NepInteractionMenuWidget.h"

void FNepInteractionSystems::DetectInteractable(
	FArcUniverse& Universe,
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
	FArcRes<FNepInteractionEvents> Events)
{
	FArcEntityHandle BestInteractableEntity = FArcEntityHandle();
	const FNepInteractable* BestInteractable = nullptr;

	{
		UWorld* World = CoreData->World.Get();
		APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
		ACharacter* Character = PlayerController ? PlayerController->GetCharacter() : nullptr;
		if (Character)
		{
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
			
			const bool bIsInteractionAvailable = Interaction->IsInteractionPossibleOnClient();
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
		if (Interactable && Interactable->Interactions.Num() == CurrentInteractableData->InteractionAvailabilities.Num())
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

				if (InteractingEntity)
				{
					Interaction->ExecuteOnClient(*InteractingEntity, CurrentInteractableData->FocusedInteractable, *Events);
					if (Interaction->ShouldExecuteOnServer())
					{
						AActor* InteractableActor = Interactable ? Interactable->Actor.Get() : nullptr;
						if (InteractableActor)
						{
							Character->Server_Interact(InteractableActor, InteractionIndex);
						}
					}
				}
			}
		}
	}
}

void FNepInteractionSystems::ExecuteLootCommand(
	FArcUniverse& Universe,
	FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
	FArcRes<FNepInteractionEvents> InteractionEvents,
	FArcRes<FNepCharacterEvents> CharacterEvents)
{
	if (InteractionEvents->bLootTarget)
	{
		if (FNepItemContainer* Container = Universe.GetComponent<FNepItemContainer>(CurrentInteractableData->FocusedInteractable))
		{
			CharacterEvents->bToggleUI = true;
			CharacterEvents->bShowContainer = true;
		}
	}
}

void FNepInteractionSystems::ExecutePossessCommands(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events)
{
	for (const TPair<FArcEntityHandle, FArcEntityHandle>& PossessCommand : Events->PossessCommands)
	{
		FNepCharacterData* CharacterData_1 = Universe.GetComponent<FNepCharacterData>(PossessCommand.Get<0>());
		FNepCharacterData* CharacterData_2 = Universe.GetComponent<FNepCharacterData>(PossessCommand.Get<1>());
		
		ANepCharacter* Character_1 = CharacterData_1 ? CharacterData_1->Character.Get() : nullptr;
		ANepCharacter* Character_2 = CharacterData_2 ? CharacterData_2->Character.Get() : nullptr;

		ANepPlayerController* PlayerController = Character_1 ? Cast<ANepPlayerController>(Character_1->GetController()) : nullptr;

		if (PlayerController && Character_2)
		{
			PlayerController->Possess(Character_2);
		}
	}
}

void FNepInteractionSystems::UpdateLights(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events)
{
	for (FArcEntityHandle& LightEntity : Events->LightsToToggle)
	{
		FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(LightEntity);
		AActor* LightActor = Interactable ? Interactable->Actor.Get() : nullptr;
		if (UNepInteractableLightComponent* InteractableLight = LightActor ? LightActor->FindComponentByClass<UNepInteractableLightComponent>() : nullptr)
		{
			InteractableLight->ToggleLight();
		}
	}
	
	for (FArcEntityHandle& LightEntity : Events->LightsToRandomize)
	{
		FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(LightEntity);
		AActor* LightActor = Interactable ? Interactable->Actor.Get() : nullptr;
		if (UNepInteractableLightComponent* InteractableLight = LightActor ? LightActor->FindComponentByClass<UNepInteractableLightComponent>() : nullptr)
		{
			InteractableLight->RandomizeLightColor();
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
