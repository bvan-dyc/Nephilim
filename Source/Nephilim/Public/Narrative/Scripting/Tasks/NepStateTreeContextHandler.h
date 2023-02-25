#pragma once

#include "StateTree.h"
#include "StateTreeInstanceData.h"
#include "StateTreeExecutionContext.h"

#include "NepStateTreeContextHandler.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreeSubtreesExecutionData
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Transient)
	FStateTreeInstanceData InstanceData;
	
	UPROPERTY(Transient)
	UWorld* WorldObjContext;
	
	UPROPERTY(Transient)
	TObjectPtr<const UStateTree> RelatedStateTree;

#if WITH_GAMEPLAY_DEBUGGER
	bool bIsInitialized = false;
#endif

	FNepStateTreeSubtreesExecutionData(EForceInit forceInit)
		: InstanceData()
		, WorldObjContext(nullptr)
		, RelatedStateTree(nullptr)
	{ }
	
	FNepStateTreeSubtreesExecutionData(UWorld* inWorldObjContext, TObjectPtr<const UStateTree> inRelatedStateTree)
		: InstanceData()
		, WorldObjContext(inWorldObjContext)
		, RelatedStateTree(inRelatedStateTree)
	{ }

	bool IsValid() const
	{
		return WorldObjContext != nullptr && RelatedStateTree && InstanceData.IsValid();
	}

#if WITH_GAMEPLAY_DEBUGGER
	bool IsInitialized() const { return bIsInitialized; }
#endif

	FStateTreeExecutionContext ComposeContext() // Note: FStateTreeExecutionContext is short lived. Do not store it.
	{
#if WITH_GAMEPLAY_DEBUGGER
		bIsInitialized = true;
#endif
		return FStateTreeExecutionContext(*WorldObjContext, *RelatedStateTree, InstanceData);
	}
};

template<>
struct TStructOpsTypeTraits<FNepStateTreeSubtreesExecutionData> : public TStructOpsTypeTraitsBase2<FNepStateTreeSubtreesExecutionData>
{
	enum
	{
		WithNoInitConstructor = true
	};
};