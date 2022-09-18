// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3GameDataWidget.h"
#include "UA3_GameModeBase.h"
#include "Player/UA3PlayerState.h"


int32 UUA3GameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetUA3GameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UUA3GameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetUA3GameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UUA3GameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetUA3GameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

AUA3_GameModeBase* UUA3GameDataWidget::GetUA3GameMode() const
{
    return GetWorld() ? Cast<AUA3_GameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AUA3PlayerState* UUA3GameDataWidget::GetUA3PlayerState() const
{
    return GetOwningPlayer() ? Cast<AUA3PlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
