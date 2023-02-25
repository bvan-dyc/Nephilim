#pragma once

#include "CoreMinimal.h"


#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "NepHealthBarWidget.generated.h"

UCLASS()
class NEPHILIM_API UNepHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar = nullptr;

	void SyncHealthPercentage(float healthPercentage) const;
};
