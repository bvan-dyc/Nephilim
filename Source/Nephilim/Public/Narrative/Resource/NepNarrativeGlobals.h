#pragma once

#include "CoreMinimal.h"

#include "NepNarrativeGlobals.generated.h"

USTRUCT()
struct NEPHILIM_API FNepNarrativeGlobals
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	class UNepNarrativeTreeWrapperDataAsset* SandboxStateTree = nullptr;
};
