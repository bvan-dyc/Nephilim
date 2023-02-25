#pragma once

#include "ArcRes.h"
#include "Narrative/Resource/NepNarrativeEvents.h"
#include "UI/Resource/NepWidgetData.h"

struct FNepConversationUISystems
{
	
public:
	
	static void ConversationPanelTick(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepNarrativeEvents> NarrativeEvents);
	static void CutscenePanelTick(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepNarrativeEvents> NarrativeEvents);
	
private:
	
	static void EndOverworldConversation(FArcRes<FNepWidgetData> WidgetData);
	static void EndCutsceneConversation(FArcRes<FNepWidgetData> WidgetData);
	static void DisplayDialogue(FArcRes<FNepWidgetData> WidgetData, const UNepDialogueDataAsset* Dialogue, ENepNarrativeChannel NarrativeChannel);
};
