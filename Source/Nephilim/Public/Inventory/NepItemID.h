#pragma once

#include "CoreMinimal.h"
#include "NepItemID.generated.h"

USTRUCT()
struct FNepItemID
{
	GENERATED_BODY()

public:

	// TODO: It might be good enough to a have unique ID per inventory.
	UPROPERTY(VisibleAnywhere)
	FGuid ID;

public:

	static FNepItemID Create()
	{
		return FNepItemID { FGuid::NewGuid() };
	}

	void Reset()
	{
		ID = FGuid();
	}

	operator bool() const
	{
		return ID.IsValid();
	}
	
	bool IsValid() const
	{
		return ID.IsValid();
	}
	
	FORCEINLINE bool operator==(const FNepItemID& Other) const
	{
		return ID == Other.ID;
	}
};
