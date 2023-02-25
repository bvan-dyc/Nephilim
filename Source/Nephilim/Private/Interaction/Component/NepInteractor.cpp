#include "Interaction/Component/NepInteractor.h"
#include "ArcUniverse.h"

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
