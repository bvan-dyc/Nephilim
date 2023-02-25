#include "UI/Widget/Dialogue/NepCutsceneSpeakerWidget.h"

#include "Components/Image.h"

void UNepCutsceneSpeakerWidget::SetImage(UTexture2D* image) const
{
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(image);
	}
}

void UNepCutsceneSpeakerWidget::HideSpeaker()
{
	SetVisibility(ESlateVisibility::Hidden);
}
