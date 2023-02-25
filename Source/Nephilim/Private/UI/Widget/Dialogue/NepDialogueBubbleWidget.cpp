#include "UI/Widget/Dialogue/NepDialogueBubbleWidget.h"

#include "Components/Image.h"

#include "Components/TextBlock.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"
#include "Narrative/DataAssets/NepSpeakerDataAsset.h"

void UNepDialogueBubbleWidget::ShowMessage(const UNepDialogueDataAsset* dialogue)
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

void UNepDialogueBubbleWidget::SetTitle(const FText& title) const
{
	if (Title)
	{
		Title->SetText(title);
	}
}

void UNepDialogueBubbleWidget::SetDialogue(const FText& dialogue) const
{
	if (Content)
	{
		Content->SetText(dialogue);
	}
}

void UNepDialogueBubbleWidget::SetImage(UTexture2D* image) const
{
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(image);
	}
}

void UNepDialogueBubbleWidget::CloseBubble()
{
	SetVisibility(ESlateVisibility::Hidden);
}
