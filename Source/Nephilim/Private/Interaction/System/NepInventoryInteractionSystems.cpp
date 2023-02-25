#include "Interaction/System/NepInventoryInteractionSystems.h"
#include "Interaction/Actor/NepLongInteractionProxy.h"
#include "Interaction/Component/NepInteractable.h"
#include "Item/ActorComponent/NepContainerInventoryComponent.h"
#include "Item/Component/NepItemContainer.h"

void FNepInventoryInteractionSystems::StartLootInteractionOnClient(
	FArcUniverse& Universe,
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
			}
			
			CharacterEvents->bShowContainer = true;
			CharacterEvents->SetUIVisibilityCommand = true;
		}
	}
}

void FNepInventoryInteractionSystems::EndLootInteractionOnClient(
	FArcUniverse& Universe,
	FArcRes<FNepInteractionEvents> InteractionEvents,
	FArcRes<FNepCharacterEvents> CharacterEvents)
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
			}
			
			CharacterEvents->SetUIVisibilityCommand = false;
		}
	}
}
