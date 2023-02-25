#include "Narrative/NepNarrativeSetup.h"
#include "ArcUniverse.h"
#include "ArcScheduleBuilder.h"
#include "Narrative/Resource/NepNarrativeEvents.h"
#include "Narrative/Resource/NepNarrativeGlobals.h"
#include "Narrative/System/NepConversationUISystems.h"
#include "Narrative/System/NepNarrativeSystems.h"

void FNepNarrativeSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepNarrativeGlobals());
	Universe.AddResource(FNepNarrativeEvents());
	Universe.AddResource(FNepNarrative());

	InitScheduleBuilder
		.AddSystem(&FNepNarrativeSystems::InitNarrativeSystems);
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanupStage"), &FNepNarrativeSystems::ClearEvents)
		.AddSystem(&FNepNarrativeSystems::ExecuteTalkCommands)
		.AddSystemSeq(&FNepNarrativeSystems::CutscenesTick)
		.AddSystemSeq(&FNepNarrativeSystems::ConversationTick)
		.AddSystemSeq(&FNepConversationUISystems::CutscenePanelTick)
		.AddSystemSeq(&FNepConversationUISystems::ConversationPanelTick);
}
