#pragma once

#include "CoreMinimal.h"
#include "NepItemArray.h"
#include "NepInventory.generated.h"

UCLASS()
class UNepInventory : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY()
    FNepItemArray ItemArray;

};
