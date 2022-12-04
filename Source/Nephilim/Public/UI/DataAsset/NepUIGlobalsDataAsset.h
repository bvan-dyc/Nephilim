#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/Resource/NepUIGlobals.h"
#include "NepUIGlobalsDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepUIGlobalsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (ShowOnlyInnerProperties))
	FNepUIGlobals UIGlobals;
	
};
