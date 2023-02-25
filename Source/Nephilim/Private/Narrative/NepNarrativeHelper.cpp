#include "Narrative/NepNarrativeHelper.h"

#include "ArcEntityHandleInternal.h"
#include "StateTree.h"
#include "Narrative/NepNarrativeTypes.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"
#include "Narrative/Resource/NepNarrative.h"

TOptional<FNepNarrativePin> FNepNarrativeHelper::GetHighestPriorityPin(const UNepDialogueDataAsset* DialogueDataAsset)
{
	TOptional<FNepNarrativePin> highestPriorityPin;
	if (!DialogueDataAsset)
	{
		return DialogueDataAsset->OutgoingPin;
	}

	return highestPriorityPin;
}


void FNepNarrativeHelper::AddEntityScript(FArcEntityHandle Entity, FArcUniverse& ArcUniverse, FNepNarrative& Narrative)
{
	//@TODO(vandyck) To be Implemented
}
