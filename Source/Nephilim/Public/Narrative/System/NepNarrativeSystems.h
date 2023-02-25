#pragma once

#include "ArcECSSubsystem.h"
#include "ArcRes.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Narrative/Resource/NepNarrative.h"
#include "Narrative/Resource/NepNarrativeEvents.h"
#include "Narrative/Resource/NepNarrativeGlobals.h"
#include "Resource/ArcCoreData.h"
#include "Time/Resource/NepTime.h"

struct FNepNarrativeSystems
{
	
public:
	
	static void InitNarrativeSystems(FArcRes<FArcCoreData> CoreData, FArcRes<FNepNarrativeGlobals> NarrativeGlobals, FArcRes<FNepNarrative> Narrative);
	static void ExecuteTalkCommands(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> InteractionEvents, FArcRes<FNepNarrativeEvents> NarrativeEvents);
	static void ConversationTick(FArcRes<FNepNarrative> Narrative, FArcRes<FNepNarrativeEvents> NarrativeEvents);
	static void CutscenesTick(FArcRes<FArcCoreData> CoreData, FArcRes<FNepTime> Time, FArcRes<FNepNarrativeGlobals> NarrativeGlobals, FArcRes<FNepNarrative> Narrative, FArcRes<FNepNarrativeEvents> NarrativeEvents);
	static void ClearEvents(FArcRes<FNepNarrativeEvents> Events);

private:
	
	static void ResetFlowPlayer(FNepConversationFlowPlayer& FlowPlayer);
	static void TickEntityTrees(FArcRes<FNepNarrative> Narrative, UWorld* World);
	static void RemoveEntityTrees(FArcRes<FNepNarrative> Narrative, UWorld* World);
};
