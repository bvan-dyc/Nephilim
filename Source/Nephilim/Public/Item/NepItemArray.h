
#pragma once

#include "CoreMinimal.h"
#include "NepItem.h"
#include "NepItemArray.generated.h"

USTRUCT()
struct FNepItemArray : public FFastArraySerializer
{
    GENERATED_BODY()

public:

    UPROPERTY()
    TArray<FNepItem> Items;

public:

    bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
    {
        return FFastArraySerializer::FastArrayDeltaSerialize<FNepItem, FNepItemArray>(Items, DeltaParams, *this);
    }

};

template<>
struct TStructOpsTypeTraits<FNepItemArray> : public TStructOpsTypeTraitsBase2<FNepItemArray>
{
    enum 
    {
        WithNetDeltaSerializer = true,
    };
};
