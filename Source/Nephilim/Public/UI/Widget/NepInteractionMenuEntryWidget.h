#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepInteractionMenuEntryWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepInteractionMenuEntryWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractionText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HotkeyText;

public:

	void SetInteractionName(const FText& InteractionName) const;
	void SetInteractionNameAndHotkeyIndex(const FText& InteractionName, int32 InteractionIndex) const;

};
