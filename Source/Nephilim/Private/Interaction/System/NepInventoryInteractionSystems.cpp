#include "Interaction/System/NepInventoryInteractionSystems.h"
#include "Interaction/Actor/NepLongInteractionProxy.h"
#include "Interaction/Component/NepInteractable.h"
#include "Inventory/ActorComponent/NepContainerInventoryComponent.h"
#include "Inventory/Component/NepItemContainer.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdateManager.h"

void FNepInventoryInteractionSystems::StartLootInteractionOnClient(
	FArcUniverse& Universe,
	FArcRes<FNepWidgetData> WidgetData,
	FArcRes<FNepInteractionEvents> InteractionEvents,
	FArcRes<FNepCharacterEvents> CharacterEvents)
{
	if (Universe.IsValid(InteractionEvents->ContainerToLoot))
	{
		if (FNepItemContainer* Container = Universe.GetComponent<FNepItemContainer>(InteractionEvents->ContainerToLoot))
		{
			FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(InteractionEvents->ContainerToLoot);
			AActor* InteractableActor = Interactable ? Interactable->Actor.Get() : nullptr;
			UNepContainerInventoryComponent* ContainerComponent = InteractableActor ? InteractableActor->FindComponentByClass<UNepContainerInventoryComponent>() : nullptr;
			if (ContainerComponent)
			{
				ContainerComponent->SetIsOpened(true);
				WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_ShowUI());
				WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_SetRightInventoryPanel { ENepRightInventoryPanel::Container });
			}
			
			CharacterEvents->SetUIVisibilityCommand = true;
		}
	}
}

void FNepInventoryInteractionSystems::EndLootInteractionOnClient(
	FArcUniverse& Universe,
	FArcRes<FNepWidgetData> WidgetData,
	FArcRes<FNepInteractionEvents> InteractionEvents)
{
	if (Universe.IsValid(InteractionEvents->ContainerToStopLooting))
	{
		if (FNepItemContainer* Container = Universe.GetComponent<FNepItemContainer>(InteractionEvents->ContainerToStopLooting))
		{
			FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(InteractionEvents->ContainerToStopLooting);
			AActor* InteractableActor = Interactable ? Interactable->Actor.Get() : nullptr;
			UNepContainerInventoryComponent* ContainerComponent = InteractableActor ? InteractableActor->FindComponentByClass<UNepContainerInventoryComponent>() : nullptr;
			if (ContainerComponent)
			{
				ContainerComponent->SetIsOpened(false);
				WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_SetRightInventoryPanel { ENepRightInventoryPanel::Equipment });
			}
		}
	}
}
