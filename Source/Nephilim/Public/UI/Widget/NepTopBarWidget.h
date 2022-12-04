#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepTopBarWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepTopBarWidget : public UUserWidget
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

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
};
