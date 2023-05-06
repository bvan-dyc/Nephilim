#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepEquipmentWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UNepItemSlotWidget* HeadSlot;
	
	UPROPERTY(meta = (BindWidget))
	class UNepItemSlotWidget* BodySlot;
	
	UPROPERTY(meta = (BindWidget))
	class UNepItemSlotWidget* LegsSlot;

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

	void HandleItemSlotClicked(int32 SlotIndex) const;
	
};
