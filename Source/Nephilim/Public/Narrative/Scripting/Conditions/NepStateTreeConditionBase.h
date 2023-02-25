#pragma once

#include "Blueprint/StateTreeConditionBlueprintBase.h"

#include "NepStateTreeConditionBase.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreeConditionBase : public FStateTreeConditionBase
{
	GENERATED_BODY()
	
	FNepStateTreeConditionBase() = default;
	
	virtual bool Link(FStateTreeLinker& linker) override;
};