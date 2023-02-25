#include "UI/Widget/Dialogue/NepDialogueBubbleWithHeadWidget.h"

#include "Components/Image.h"

#include "Components/TextBlock.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"
#include "Narrative/DataAssets/NepSpeakerDataAsset.h"

void UNepDialogueBubbleWithHeadWidget::ShowMessage(const UNepDialogueDataAsset* dialogue)
{
	SetVisibility(dialogue ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);

	if (Title)
	{
		Title->SetText(dialogue->Speaker ? dialogue->Speaker->SpeakerName : FText::GetEmpty());
	}
	if (Content)
	{
		Content->SetText(dialogue->Text);
	}
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(dialogue->Speaker ? dialogue->Speaker->CharacterImage : nullptr);
	}
}

void UNepDialogueBubbleWithHeadWidget::SetTitle(const FText& title) const
{
	if (Title)
	{
		Title->SetText(title);
	}
}

void UNepDialogueBubbleWithHeadWidget::SetDialogue(const FText& dialogue) const
{
	if (Content)
	{
		Content->SetText(dialogue);
	}
}

void UNepDialogueBubbleWithHeadWidget::SetImage(UTexture2D* image) const
{
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(image);
	}
}

void UNepDialogueBubbleWithHeadWidget::CloseBubble()
{
	SetVisibility(ESlateVisibility::Hidden);
}
