#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepItemSlotWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UImage* Icon;

public:

	void SetItem(const struct FNepItem& Item);
};
