#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepPlayerInventoryWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	
	UPROPERTY(meta = (BindWidget))
	class UNepInventoryWidget* InventoryWidget = nullptr;

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
	
	void HandleItemClicked(const struct FNepItemID& ItemID) const;
};
