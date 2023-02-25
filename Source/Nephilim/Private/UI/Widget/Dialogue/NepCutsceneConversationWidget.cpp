#include "UI/Widget/Dialogue/NepCutsceneConversationWidget.h"

#include "Narrative/DataAssets/NepDialogueDataAsset.h"
#include "Narrative/DataAssets/NepSpeakerDataAsset.h"
#include "UI/Resource/NepWidgetData.h"
#include "UI/Widget/Dialogue/NepDialogueBubbleWidget.h"

void UNepCutsceneConversationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
	{
		WidgetData->CutsceneConversationWidget = this;
	}

	CloseCutscene();
}

void UNepCutsceneConversationWidget::StartDialogue(const UNepDialogueDataAsset* dialogue) const
{
	if (!dialogue)
	{
		CloseCutscene();
		
		return;
	}
	
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->ShowMessage(dialogue);
	}

	if (LeftHandSpeaker)
	{
		LeftHandSpeaker->SetImage(dialogue->Speaker ? dialogue->Speaker->CharacterImage : nullptr);
		LeftHandSpeaker->SetVisibility(dialogue->Speaker ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}

	if (RightHandSpeaker)
	{
		//@@TODO(vandyck) hide since not yet implemented
		RightHandSpeaker->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UNepCutsceneConversationWidget::FillWithData(const FText& speakerName, const FText& dialogueText, const UNepSpeakerDataAsset* leftHandSpeaker, const UNepSpeakerDataAsset* rightHandSpeaker) const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->SetTitle(speakerName);
		DialogueBubbleWidget->SetDialogue(dialogueText);
	}

	if (LeftHandSpeaker)
	{
		LeftHandSpeaker->SetImage(leftHandSpeaker ? leftHandSpeaker->CharacterImage : nullptr);
		LeftHandSpeaker->SetVisibility(leftHandSpeaker ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}

	if (RightHandSpeaker)
	{
		RightHandSpeaker->SetImage(rightHandSpeaker ? rightHandSpeaker->CharacterImage : nullptr);
		RightHandSpeaker->SetVisibility(rightHandSpeaker ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}
}

void UNepCutsceneConversationWidget::EndConversation() const
{
	CloseCutscene();
}

void UNepCutsceneConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNepCutsceneConversationWidget::CloseCutscene() const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (LeftHandSpeaker)
	{
		LeftHandSpeaker->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (RightHandSpeaker)
	{
		RightHandSpeaker->SetVisibility(ESlateVisibility::Hidden);
	}
}
