#pragma once

#include "CoreMinimal.h"

struct FNepWidgetData
{
public:
    
    TWeakObjectPtr<class UNepHUDWidget> HUDWidget;
    TWeakObjectPtr<class UNepTopBarWidget> TopBarWidget;
    TWeakObjectPtr<class UNepInventoryWidget> InventoryWidget;
    TWeakObjectPtr<class UNepEquipmentWidget> EquipmentWidget;
    TWeakObjectPtr<class UNepContainerInventoryWidget> ContainerInventoryWidget;
    TWeakObjectPtr<class UNepInteractionMenuWidget> InteractionMenuWidget;
    bool bUIVisible = false;

public:
    static FNepWidgetData* Get(const UObject* context);
};
