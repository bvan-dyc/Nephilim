#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepContainerInventoryWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepContainerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	
	UPROPERTY(meta = (BindWidget))
	class UNepInventoryWidget* InventoryWidget = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInAnimation;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOutAnimation;

	UPROPERTY()
	TObjectPtr<class ANepInventoryInteractionProxy> InteractionProxy = nullptr;

	TWeakObjectPtr<class UNepInventory> CurrentInventory;
	
	bool bIsVisible = false;
	
	TSharedPtr<struct FNepWidgetUpdater> WidgetUpdater;

public:

	void InitializeFromProxy(class ANepInventoryInteractionProxy& Proxy);

protected:

	virtual void NativeOnInitialized() override;

private:
	
	void Update();
	
	void FadeIn();
	void FadeOut();

	void HandleItemClicked(const struct FNepItemID& ItemID) const;
};
