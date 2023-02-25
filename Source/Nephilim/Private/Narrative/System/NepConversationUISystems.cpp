#include "Narrative/System/NepConversationUISystems.h"

#include "UI/Resource/NepWidgetData.h"
#include "UI/Widget/Dialogue/NepConversationWidget.h"
#include "UI/Widget/Dialogue/NepCutsceneConversationWidget.h"

void FNepConversationUISystems::ConversationPanelTick(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepNarrativeEvents> NarrativeEvents)
{
	for (const FNepShowDialogueRequest& dialogueRequest : NarrativeEvents->ShowOverworldDialogueRequests)
	{
		if (const UNepConversationWidget* conversationWidget = WidgetData->ConversationWidget.Get())
		{
			if (dialogueRequest.DialogueDataAsset)
			{
				conversationWidget->StartDialogue(dialogueRequest.DialogueDataAsset);
			}
			else
			{
				conversationWidget->EndConversation();
			}
		}
	}
}

void FNepConversationUISystems::CutscenePanelTick(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepNarrativeEvents> NarrativeEvents)
{
	for (const FNepShowDialogueRequest& dialogueRequest : NarrativeEvents->ShowCutsceneDialogueRequests)
	{
		if (const UNepCutsceneConversationWidget* conversationWidget = WidgetData->CutsceneConversationWidget.Get())
		{
			if (dialogueRequest.DialogueDataAsset)
			{
				conversationWidget->StartDialogue(dialogueRequest.DialogueDataAsset);
			}
			else
			{
				conversationWidget->EndConversation();
			}
		}
	}
}
