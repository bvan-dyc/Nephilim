#pragma once

#include "NepStateTreeContextHandler.h"

#include "StateTree.h"
#include "StateTreeReference.h"
#include "StateTreeTaskBase.h"

#include "NepStateTreeSubtreesTask.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreeSubtreesTaskInstanceData
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient)
	TArray<FNepStateTreeSubtreesExecutionData> ExecutionData;
};

USTRUCT(meta = (DisplayName = "Subtrees Task"))
struct NEPHILIM_API FNepStateTreeSubtreesTask : public FStateTreeTaskBase
{
	GENERATED_BODY()
	
public:
	typedef FNepStateTreeSubtreesTaskInstanceData FInstanceDataType;

protected:

	UPROPERTY(EditAnywhere, Category="Parameter")
	TArray<FStateTreeReference> SubtreeDataAssets;

	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bOnlyOneSuccessNecessary = false;

public:
	
	FNepStateTreeSubtreesTask() = default;

	virtual const UStruct* GetInstanceDataType() const override;
	virtual bool Link(FStateTreeLinker& linker) override;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& context, const FStateTreeTransitionResult& transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& context, const float deltaTime) const override;
};
