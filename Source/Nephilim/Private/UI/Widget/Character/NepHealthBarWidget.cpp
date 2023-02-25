#include "UI/Widget/Character/NepHealthBarWidget.h"

void UNepHealthBarWidget::SyncHealthPercentage(float healthPercentage) const
{
	if (healthPercentage < 0) { return; }

	if (HealthBar)
	{
		HealthBar->SetPercent(healthPercentage);
	}
}
