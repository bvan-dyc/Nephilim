#pragma once

#include "CoreMinimal.h"
#include "NepUIGlobals.generated.h"

USTRUCT()
struct FNepUIGlobals
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UNepHUDWidget> HUDWidget = nullptr;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> MinimalInteractionIndicatorWidget = nullptr;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> CharacterInteractionIndicatorWidget = nullptr;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UNepItemSlotWidget> ItemSlotWidget = nullptr;
};
