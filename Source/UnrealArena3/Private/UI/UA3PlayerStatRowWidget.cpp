// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUA3PlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock)
        return;
    PlayerNameTextBlock->SetText(Text);
}

void UUA3PlayerStatRowWidget::SetKills(const FText& Text)
{
    if (!KillsTextBlock)
        return;
    KillsTextBlock->SetText(Text);
}

void UUA3PlayerStatRowWidget::SetDeaths(const FText& Text)
{
    if (!DeathsTextBlock)
        return;
    DeathsTextBlock->SetText(Text);
}

void UUA3PlayerStatRowWidget::SetTeam(const FText& Text)
{
    if (!TeamTextBlock)
        return;
    TeamTextBlock->SetText(Text);
}

void UUA3PlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage)
        return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UUA3PlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
    if (!TeamImage)
        return;
    TeamImage->SetColorAndOpacity(Color);
}
