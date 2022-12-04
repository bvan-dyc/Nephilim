#pragma once

#include "ArcEntityHandle.h"

struct FNepInteractionEvents
{
    // Client
    bool bUpdateInteractionMenu = false;
    bool bCollapseInteractionMenu = false;
    
    bool bInteractionKeyPressed = false;
    TOptional<int32> SelectedInteractionIndex;
    
    bool bLootTarget = false;

    // Server
    TArray<TPair<FArcEntityHandle, FArcEntityHandle>> PossessCommands;
    TArray<FArcEntityHandle> LightsToToggle;
    TArray<FArcEntityHandle> LightsToRandomize;
};
