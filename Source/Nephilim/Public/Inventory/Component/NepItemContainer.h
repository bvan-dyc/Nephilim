#pragma once

#include "CoreMinimal.h"
#include "Inventory/NepInventory.h"
#include "NepItemContainer.generated.h"

USTRUCT()
struct FNepItemContainer
{
    GENERATED_BODY()

public:
    
    TWeakObjectPtr<UNepInventory> Inventory;

public:
    
    FNepItemContainer() = default;
    explicit FNepItemContainer(class UNepInventory& InInventory);

};
