// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3SpectatorWidget.h"
#include "UA3Utils.h"
#include "Components/UA3RespawnComponent.h"

bool UUA3SpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = UA3Utils::GetUA3PlayerComponent<UUA3RespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
