#include "UI/Widget/Character/NepPlayerHealthBarWidget.h"

void UNepPlayerHealthBarWidget::SyncHealthPercentage(float healthPercentage) const
{
	if (healthPercentage < 0) { return; }

	if (HealthBar)
	{
		HealthBar->SetPercent(healthPercentage);
	}
}
