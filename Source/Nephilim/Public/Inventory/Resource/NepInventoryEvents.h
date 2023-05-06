#pragma once

#include "Inventory/NepItemID.h"

struct FNepInventoryEvents
{
public:
    
    // Client
    TArray<TTuple<FNepItemID, bool>> ItemMoveCommandsOnClient; // ItemID and whether to move from interactor to interactable or into the reverse direction.
    TArray<TWeakObjectPtr<class UNepInventory>> ChangedInventories;

    // Server
    //TArray<TTuple<TWeakObjectPtr<class ANepInventoryInteractionProxy>, uint64, bool>> ItemMoveCommandsOnServer;

public:

    static FNepInventoryEvents* Get(const UObject* context);
};
