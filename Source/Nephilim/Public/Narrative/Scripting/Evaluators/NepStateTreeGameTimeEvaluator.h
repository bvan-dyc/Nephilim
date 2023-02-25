#pragma once

#include "NepStateTreeEvaluatorBase.h"
#include "NepStateTreeGameTimeEvaluator.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreeGameTimeEvaluatorInstanceData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category= "Parameter")
	int32 Seconds = 0;
};

USTRUCT(meta = (DisplayName = "Game Time Evaluator"))
struct NEPHILIM_API FNepStateTreeGameTimeEvaluator : public FNepStateTreeEvaluatorBase
{
	GENERATED_BODY()

public:
	typedef FNepStateTreeGameTimeEvaluatorInstanceData FInstanceDataType;

	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	virtual void Tick(FStateTreeExecutionContext& context, const float deltaTime) const override;
	virtual const UStruct* GetInstanceDataType() const override;
};