#pragma once

#include "CoreMinimal.h"
#include "NepItemID.h"
#include "Engine/NetSerialization.h"
#include "NepItem.generated.h"

USTRUCT()
struct FNepItem : public FFastArraySerializerItem
{
    GENERATED_BODY()

public:
    
    UPROPERTY(EditAnywhere)
    const class UNepItemDataAsset* DataAsset = nullptr;

	UPROPERTY(VisibleAnywhere)
	FNepItemID ID;

public:

    FNepItem() = default;

	void Reset()
	{
		DataAsset = nullptr;
		ID.Reset();
	}
	
	bool IsValid() const { return DataAsset && ID.IsValid(); }
    
	//void PreReplicatedRemove(const struct FExampleArray& InArraySerializer);
	//void PostReplicatedAdd(const struct FExampleArray& InArraySerializer);
	//void PostReplicatedChange(const struct FExampleArray& InArraySerializer);
};
