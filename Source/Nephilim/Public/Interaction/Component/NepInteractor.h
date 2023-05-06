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

    static FNepInteractor* GetLocalInteractor(const UObject* Context);

    template<typename T>
    static T* GetLocalProxy(const UObject* Context)
    {
        FNepInteractor* LocalInteractor = GetLocalInteractor(Context);
        for (TWeakObjectPtr<class ANepLongInteractionProxy> ProxyWeak : LocalInteractor->InteractionProxies)
        {
            if (T* ProxyCasted = Cast<T>(ProxyWeak))
            {
                return ProxyCasted;
            }
        }
        return nullptr;
    }
};
