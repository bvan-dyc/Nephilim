#pragma once

#include "CoreMinimal.h"
#include "Item/NepInventory.h"
#include "NepItemContainer.generated.h"

USTRUCT()
struct FNepItemContainer
{
    GENERATED_BODY()

public:
    
    TWeakObjectPtr<UNepInventory> Inventory;

};
