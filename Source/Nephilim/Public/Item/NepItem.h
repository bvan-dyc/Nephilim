#pragma once

#include "CoreMinimal.h"
//#include "UObject/StrongObjectPtr.h"
//#include "Item/DataAsset/T2ItemDataAsset.h"
#include "Engine/NetSerialization.h"
#include "NepItem.generated.h"

USTRUCT()
struct FNepItem : public FFastArraySerializerItem
{
    GENERATED_BODY()

public:
    
    //TStrongObjectPtr<const UT2ItemDataAsset> DataAsset;

    UPROPERTY(EditAnywhere)
    const class UNepItemDataAsset* DataAsset;

    UPROPERTY(VisibleAnywhere)
    uint64 ID;

public:

    FNepItem() = default;
    
	//void PreReplicatedRemove(const struct FExampleArray& InArraySerializer);
	//void PostReplicatedAdd(const struct FExampleArray& InArraySerializer);
	//void PostReplicatedChange(const struct FExampleArray& InArraySerializer);
};
