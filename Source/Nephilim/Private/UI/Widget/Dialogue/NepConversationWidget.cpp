#include "UI/Widget/Dialogue/NepConversationWidget.h"

#include "Narrative/DataAssets/NepDialogueDataAsset.h"
#include "UI/Resource/NepWidgetData.h"
#include "UI/Widget/Dialogue/NepDialogueBubbleWidget.h"

void UNepConversationWidget::FillWithData(const FText& speakerName, const FText& dialogueText, UTexture2D* speaker) const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->SetTitle(speakerName);
		DialogueBubbleWidget->SetDialogue(dialogueText);
		DialogueBubbleWidget->SetImage(speaker);
	}
}

void UNepConversationWidget::StartDialogue(const UNepDialogueDataAsset* dialogue) const
{
	if (!dialogue)
	{
		if (DialogueBubbleWidget)
		{
			DialogueBubbleWidget->CloseBubble();
		}
		
		return;
	}
	
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->ShowMessage(dialogue);
	}
}

void UNepConversationWidget::EndConversation() const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->CloseBubble();
	}
}

void UNepConversationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
	{
		WidgetData->ConversationWidget = this;
	}
	
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->CloseBubble();
	}
}

void UNepConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
