#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepItemSlotWidget.generated.h"

DECLARE_DELEGATE_OneParam(FNepItemSlotClickedDelegate, int32);

UCLASS(Abstract)
class NEPHILIM_API UNepItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FNepItemSlotClickedDelegate OnItemSlotClicked;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Icon = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Background = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button = nullptr;

	int32 SlotIndex = INDEX_NONE;

public:

	void SetItem(const struct FNepItem* Item);
	void SetSlotIndex(int32 InSlotIndex);

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void HandleClicked();
	
};
