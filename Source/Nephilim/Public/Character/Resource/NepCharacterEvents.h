#pragma once

#include "ArcEntityHandleInternal.h"

struct FNepCharacterEvents
{
    TArray<TPair<FArcEntityHandle, TWeakObjectPtr<class ANepCharacter>>> CharacterCreatedEvents;
    TArray<FArcEntityHandle> CharacterMeshesChangedEvents;
    bool bToggleUI = false;
    bool bShowContainer = false;
};
