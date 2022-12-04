#pragma once

#include "ArcEntityHandle.h"

struct FNepCurrentInteractableData
{
public:
    
    FArcEntityHandle FocusedInteractable = FArcEntityHandle();
    TArray<bool> InteractionAvailabilities;
    int32 NumAvailableInteractions = 0;
};
