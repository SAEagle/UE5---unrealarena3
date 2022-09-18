// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UUA3HealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar)
        return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) //
                                         ? ESlateVisibility::Hidden
                                         : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}
