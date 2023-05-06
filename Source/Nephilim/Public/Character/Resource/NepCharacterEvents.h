#pragma once

#include "ArcEntityHandleInternal.h"
#include "Inventory/ItemConfig/NepArmorItemConfig.h"

struct FNepCharacterEvents
{
    TArray<TPair<FArcEntityHandle, TWeakObjectPtr<class ANepCharacter>>> CharacterCreatedEvents;
    
    TArray<FArcEntityHandle> CharacterMeshesChangedEvents;

    // TODO: Currently unused
    TArray<TPair<FArcEntityHandle, ENepArmorType>> UnequipEvents;
    
    bool bToggleUI = false;
    TOptional<bool> SetUIVisibilityCommand;
};
