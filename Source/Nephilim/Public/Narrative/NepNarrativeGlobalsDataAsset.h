#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Resource/NepNarrativeGlobals.h"
#include "NepNarrativeGlobalsDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepNarrativeGlobalsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	FNepNarrativeGlobals NarrativeGlobals;
};
