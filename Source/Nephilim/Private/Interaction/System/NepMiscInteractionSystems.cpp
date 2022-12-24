#include "Interaction/System/NepMiscInteractionSystems.h"
#include "Character/Actor/NepCharacter.h"
#include "Character/Actor/NepPlayerController.h"
#include "Character/Component/NepCharacterData.h"
#include "Interaction/ActorComponent/NepInteractableLightComponent.h"
#include "Interaction/Component/NepInteractable.h"

void FNepMiscInteractionSystems::ExecutePossessCommands(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events)
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

void FNepMiscInteractionSystems::UpdateLights(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events)
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
