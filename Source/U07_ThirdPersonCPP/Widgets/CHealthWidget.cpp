#include "CHealthWidget.h"
#include "components/ProgressBar.h"

void UCHealthWidget::UpdateHealth_Implementation(float InCurrentHP, float InMaxHP)
{
	HealthBar->SetPercent(InCurrentHP / InMaxHP);
}
