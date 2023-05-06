#include "Interaction/Component/NepInteractor.h"
#include "ArcECSSubsystem.h"
#include "ArcUniverse.h"
#include "Resource/ArcCoreData.h"
#include "GameFramework/Character.h"

bool FNepInteractor::IsAttentionOccupied(const FArcUniverse& Universe, FArcEntityHandle InteractorEntity)
{
	FNepInteractor* Interactor = Universe.GetComponent<FNepInteractor>(InteractorEntity);
	return Interactor && Interactor->bIsAttentionOccupied;
}

bool FNepInteractor::IsBodyOccupied(const FArcUniverse& Universe, FArcEntityHandle InteractorEntity)
{
	FNepInteractor* Interactor = Universe.GetComponent<FNepInteractor>(InteractorEntity);
	return Interactor && Interactor->bIsBodyOccupied;
}

FNepInteractor* FNepInteractor::GetLocalInteractor(const UObject* Context)
{
	UWorld* World = Context ? Context->GetWorld() : nullptr;
	APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
	ACharacter* Character = PlayerController ? PlayerController->GetCharacter() : nullptr;

	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(World);
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	FArcCoreData* CoreData = Universe ? Universe->GetResource<FArcCoreData>() : nullptr;

	FArcEntityHandle* CharacterEntity = Character && CoreData ? CoreData->EntitiesByActor.Find(Character) : nullptr;
	return CharacterEntity ? Universe->GetComponent<FNepInteractor>(*CharacterEntity) : nullptr;
}
