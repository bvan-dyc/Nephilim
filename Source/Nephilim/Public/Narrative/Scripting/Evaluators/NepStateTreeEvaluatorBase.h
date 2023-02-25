#pragma once

#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "NepStateTreeEvaluatorBase.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreeEvaluatorBase : public FStateTreeEvaluatorBase
{
	GENERATED_BODY()

public:
	
	virtual bool Link(FStateTreeLinker& linker) override;
};