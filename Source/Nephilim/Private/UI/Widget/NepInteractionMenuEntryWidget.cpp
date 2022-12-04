#include "UI/Widget/NepInteractionMenuEntryWidget.h"
#include "Components/TextBlock.h"

void UNepInteractionMenuEntryWidget::SetInteractionName(const FText& InteractionName) const
{
	if (InteractionText)
	{
		InteractionText->SetText(InteractionName);
	}
}

void UNepInteractionMenuEntryWidget::SetInteractionNameAndHotkeyIndex(const FText& InteractionName, int32 InteractionIndex) const
{
	if (InteractionText)
	{
		InteractionText->SetText(InteractionName);
	}
	
	if (HotkeyText)
	{
		HotkeyText->SetText(FText::AsNumber(InteractionIndex + 1));
	}
}
