#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactions/NepInteraction.h"

struct FNepInteractable
{
    TWeakObjectPtr<AActor> Actor;
    TArray<TUniquePtr<FNepInteraction>> Interactions;
};
