#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "StateTreeReference.h"

#include "NepNarrativeTreeWrapperDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepNarrativeTreeWrapperDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere)
	FStateTreeReference SandboxStateTree;
};
