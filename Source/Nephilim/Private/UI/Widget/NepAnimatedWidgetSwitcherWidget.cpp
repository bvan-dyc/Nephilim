// Copyright Limbic Entertainment GmbH, All Rights Reserved.

#include "UI/Widget/NepAnimatedWidgetSwitcherWidget.h"
#include "Components/SizeBox.h"
#include "Components/NamedSlot.h"
#include "Components/Overlay.h"

void UNepAnimatedWidgetSwitcherWidget::SetActiveWidgetIndex(int32 Index)
{
	UOverlay* Overlay = Content ? Cast<UOverlay>(Content->GetContent()) : nullptr;
	if (!Overlay || Index >= Overlay->GetChildrenCount() || Index == ActiveWidgetIndex) { return; }

	PreviousWidgetIndex = ActiveWidgetIndex;
	ActiveWidgetIndex = Index;
	bIsAnimating = true;
	TimeSinceAnimationStart = 0.0f;
	
	if (UWidget* ActiveWidget = Overlay->GetChildAt(ActiveWidgetIndex))
	{
		ActiveWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UNepAnimatedWidgetSwitcherWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UOverlay* Overlay = Content ? Cast<UOverlay>(Content->GetContent()) : nullptr;
	if (!Overlay) { return; }
	
	for (int32 i = 0; i < Overlay->GetChildrenCount(); ++i)
	{
		if (UWidget* Child = Overlay->GetChildAt(i))
		{
			Child->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (ContainerSizeBox)
	{
		ContainerSizeBox->SetWidthOverride(0.0f);
		ContainerSizeBox->SetHeightOverride(0.0f);
	}
}

void UNepAnimatedWidgetSwitcherWidget::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);

	if (!ContainerSizeBox || !Content || !bIsAnimating) { return; }
	UOverlay* Overlay = Cast<UOverlay>(Content->GetContent());
	if (!Overlay) { return; }

	UWidget* PreviousWidget = Overlay->GetChildAt(PreviousWidgetIndex);
	UWidget* ActiveWidget = Overlay->GetChildAt(ActiveWidgetIndex);
	
	const float WidthStart = PreviousWidget ? static_cast<float>(PreviousWidget->GetDesiredSize().X) : 0.0f;
	const float WidthTarget = ActiveWidget ? static_cast<float>(ActiveWidget->GetDesiredSize().X) : 0.0f;
	
	const float HeightStart = PreviousWidget ? static_cast<float>(PreviousWidget->GetDesiredSize().Y) : 0.0f;
	const float HeightTarget = ActiveWidget ? static_cast<float>(ActiveWidget->GetDesiredSize().Y) : 0.0f;
	
	const float Alpha = FMath::Clamp(TimeSinceAnimationStart / (AnimationDuration > 0 ? AnimationDuration : 1.0f), 0.0f, 1.0f);

	TimeSinceAnimationStart += DeltaTime;
	const float CurrentWidth = FMath::InterpEaseInOut(
		WidthStart,
		WidthTarget,
		Alpha,
		4.0f
	);
	const float CurrentHeight = FMath::InterpEaseInOut(
		HeightStart,
		HeightTarget,
		Alpha,
		4.0f
	);

	ContainerSizeBox->SetWidthOverride(CurrentWidth);
	ContainerSizeBox->SetHeightOverride(CurrentHeight);

	if (PreviousWidget)
	{
		PreviousWidget->SetRenderOpacity(1.0f - Alpha);
	}
	if (ActiveWidget)
	{
		ActiveWidget->SetRenderOpacity(Alpha);
	}

	if (Alpha >= 1.0f)
	{
		bIsAnimating = false;
		if (PreviousWidget)
		{
			PreviousWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
