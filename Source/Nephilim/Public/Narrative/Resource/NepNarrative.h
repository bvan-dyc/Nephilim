#pragma once

#include "ArcEntityHandle.h"
#include "NepNarrativeEvents.h"
#include "NepNarrativeTreeWrapper.h"
#include "Narrative/NepNarrativeTypes.h"
#include "Narrative/Scripting/NepStateTreeTypes.h"

#include "NepNarrative.generated.h"

USTRUCT()
struct NEPHILIM_API FNepNarrative
{
	GENERATED_BODY()

public:
	
	FNepConversationFlowPlayer DialogueFlowPlayer;

	FNepConversationFlowPlayer CutsceneFlowPlayer;

	FNepNarrativeTreeWrapper NarrativeTree;

	TArray<FNepEntityScriptingData> EntityTrees;
	
	TMap<FName, struct FNepNarrativeVariableData> NarrativeVariables;
	
	bool bStartedMainTree = false;
	bool bStoppedMainTree = false;
};
