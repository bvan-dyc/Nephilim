#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepAnimatedWidgetSwitcherWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepAnimatedWidgetSwitcherWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class USizeBox* ContainerSizeBox;

	UPROPERTY(meta = (BindWidget))
	class UNamedSlot* Content;
	
	UPROPERTY(EditDefaultsOnly)
	float AnimationDuration = 0.15f;

	int32 ActiveWidgetIndex = INDEX_NONE;

	bool bIsAnimating = false;
	bool bIsCollapsed = false;

	float TimeSinceAnimationStart = 0.0f;

	int32 PreviousWidgetIndex = INDEX_NONE;

public:

	void SetActiveWidgetIndex(int32 Index);
	int32 GetActiveWidgetIndex() const { return ActiveWidgetIndex; }

protected:
	
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

};
