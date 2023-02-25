#pragma once

#include "ArcEntityHandle.h"

#include "Narrative/Resource/NepNarrativeTreeWrapper.h"

#include "NepStateTreeTypes.generated.h"

USTRUCT()
struct NEPHILIM_API FNepEntityScriptingData
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Transient)
	class UStateTree* StateTree = nullptr;

	UPROPERTY(Transient)
	FNepNarrativeTreeWrapper TreeWrapper;
	
	FArcEntityHandle EntityHandle = FArcEntityHandle();

	bool bStateTreeStarted = false;
	bool bStateTreeStopped = false;

	FNepEntityScriptingData() {}
};
