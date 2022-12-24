#include "Interaction/NepInteractionHelper.h"
#include "ArcUniverse.h"
#include "Character/Actor/NepCharacter.h"
#include "Character/Component/NepCharacterData.h"
#include "Interaction/Component/NepInteractable.h"

bool FNepInteractionHelper::IsInInteractionRange(const FArcUniverse& Universe, FArcEntityHandle& InteractorEntity, FArcEntityHandle& InteractableEntity)
{
	FNepCharacterData* CharacterData = Universe.GetComponent<FNepCharacterData>(InteractorEntity);
	ANepCharacter* Character = CharacterData ? CharacterData->Character.Get() : nullptr;
	FNepInteractable* Interactable = Universe.GetComponent<FNepInteractable>(InteractableEntity);
	AActor* InteractableActor = Interactable ? Interactable->Actor.Get() : nullptr;
	if (!Character || !InteractableActor) { return false; }
	
	return FVector::DistSquared(Character->GetActorLocation(), InteractableActor->GetActorLocation()) < FMath::Square(300.0f);
}
