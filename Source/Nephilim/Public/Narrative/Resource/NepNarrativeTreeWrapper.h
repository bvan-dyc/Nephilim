#pragma once

#include "StateTreeExecutionContext.h"
#include "Narrative/Scripting/Tasks/NepStateTreeContextHandler.h"

#include "NepNarrativeTreeWrapper.generated.h"

USTRUCT()
struct NEPHILIM_API FNepNarrativeTreeWrapper
{
	GENERATED_BODY()

public:

	UPROPERTY(Transient)
	FNepStateTreeSubtreesExecutionData ExecutionData;

	FNepNarrativeTreeWrapper() : ExecutionData(nullptr, nullptr) { }
	FNepNarrativeTreeWrapper(UWorld* inWorldObjContext, TObjectPtr<const UStateTree> inRelatedStateTree)
		: ExecutionData(inWorldObjContext, inRelatedStateTree)
	{ }
};
