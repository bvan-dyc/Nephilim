#pragma once

#include "NepStateTreeEvaluatorBase.h"
#include "NepStateTreeNarrativeVariableEvaluator.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreeCustomVariableEvaluatorInstanceData
{
	GENERATED_BODY()

	// Used to refer to the variable; Must be unique!
	UPROPERTY(EditAnywhere, Category= "Parameter")
	FName VariableID;
	
	UPROPERTY(EditAnywhere, Category= "Parameter")
	bool bBool = false;

	UPROPERTY(EditAnywhere, Category= "Parameter")
	int32 Integer = 0;

	UPROPERTY(EditAnywhere, Category= "Parameter")
	double Double = 0.0;

	UPROPERTY(EditAnywhere, Category= "Parameter")
	FVector Vector = FVector::ZeroVector;
};

USTRUCT(meta = (DisplayName = "Custom Narrative Variable"))
struct NEPHILIM_API FNepStateTreeNarrativeVariableEvaluator : public FNepStateTreeEvaluatorBase
{
	GENERATED_BODY()

public:
	
	typedef FNepStateTreeCustomVariableEvaluatorInstanceData FInstanceDataType;
	
	virtual const UStruct* GetInstanceDataType() const override;
	virtual void TreeStart(FStateTreeExecutionContext& context) const override;
	virtual void Tick(FStateTreeExecutionContext& context, const float deltaTime) const override;
};
