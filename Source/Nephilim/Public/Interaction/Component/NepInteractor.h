#pragma once

#include "CoreMinimal.h"

struct FNepInteractor
{
public:
    TArray<TWeakObjectPtr<class ANepLongInteractionProxy>> InteractionProxies;

    bool bIsAttentionOccupied = false;
    bool bIsBodyOccupied = false;

public:
    static bool IsAttentionOccupied(const class FArcUniverse& Universe, class FArcEntityHandle InteractorEntity);
    static bool IsBodyOccupied(const class FArcUniverse& Universe, class FArcEntityHandle InteractorEntity);
};
