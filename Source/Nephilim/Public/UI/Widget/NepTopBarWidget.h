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
	
	bool bIsVisible = false;
	
	TSharedPtr<struct FNepWidgetUpdater> WidgetUpdater;

protected:

	virtual void NativeOnInitialized() override;

private:

	void Update();
	
	void FadeIn();
	void FadeOut();
	
};
