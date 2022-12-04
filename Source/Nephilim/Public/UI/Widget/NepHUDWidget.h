#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArcEntityHandle.h"
#include "NepHUDWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canvas;

	UPROPERTY()
	UWidget* FocusedInteractableWidget;

	FArcEntityHandle FocusedInteractable;

public:

	void UpdateInteractableIndicator();
};
