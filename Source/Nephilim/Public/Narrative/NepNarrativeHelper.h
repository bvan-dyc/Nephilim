#pragma once
#include "ArcEntityHandleInternal.h"
#include "Resource/NepNarrative.h"

struct FNepNarrativeHelper
{
	static TOptional<struct FNepNarrativePin> GetHighestPriorityPin(const class UNepDialogueDataAsset* DialogueDataAsset);
	static void AddEntityScript(FArcEntityHandle Entity, FArcUniverse& ArcUniverse, FNepNarrative& Narrative);
};
