#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepContainerInventoryWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepContainerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInAnimation;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOutAnimation;

public:

	void FadeIn();
	void FadeOut();

protected:

	void NativeOnInitialized() override;
	void NativeConstruct() override;
	
};
