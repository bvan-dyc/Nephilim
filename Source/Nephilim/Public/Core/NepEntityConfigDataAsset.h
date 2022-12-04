#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NepEntityConfigDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepEntityConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UArcBaseComponent*> ComponentConfigs;

};
