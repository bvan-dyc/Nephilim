#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/NepItemID.h"
#include "NepInventoryWidget.generated.h"

DECLARE_DELEGATE_OneParam(FNepItemClickedDelegate, const FNepItemID&);

UCLASS(Abstract)
class NEPHILIM_API UNepInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FNepItemClickedDelegate OnItemClicked;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* SlotsContainer = nullptr;
	
	UPROPERTY()
	TArray<class UNepItemSlotWidget*> ItemSlots;

	UPROPERTY(EditAnywhere)
	int32 NumPreviewSlots = 25;

	TWeakObjectPtr<class UNepInventory> CurrentInventory;

	TSharedPtr<struct FNepWidgetUpdater> WidgetUpdater;

public:

	void SetInventory(class UNepInventory* Inventory);

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;

private:

	void Update();
	void UpdateContent(class UNepInventory& Inventory);

	void HandleItemSlotClicked(int32 SlotIndex) const;
};
