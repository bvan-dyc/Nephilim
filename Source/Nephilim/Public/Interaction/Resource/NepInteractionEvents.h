#pragma once

#include "ArcEntityHandle.h"

struct FNepInteractionEvents
{
    // Client
    bool bUpdateInteractionMenu = false;
    bool bCollapseInteractionMenu = false;
    
    bool bInteractionKeyPressed = false;
    TOptional<int32> SelectedInteractionIndex;
    
    TArray<TWeakObjectPtr<class ANepLongInteractionProxy>> LongInteractionsToEndOnClient;
    
    FArcEntityHandle ContainerToLoot;
    FArcEntityHandle ContainerToStopLooting;

    // Server
    TArray<TPair<FArcEntityHandle, FArcEntityHandle>> PossessCommands;
    TArray<TPair<FArcEntityHandle, FArcEntityHandle>> TalkCommands;
    TArray<FArcEntityHandle> LightsToToggle;
    TArray<FArcEntityHandle> LightsToRandomize;
    TArray<TWeakObjectPtr<class ANepLongInteractionProxy>> LongInteractionsToEndOnServer;
};
