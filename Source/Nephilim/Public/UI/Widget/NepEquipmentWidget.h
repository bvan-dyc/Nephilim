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

public:

	void FadeIn();
	void FadeOut();

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:

	void UpdateItems();
	
};
