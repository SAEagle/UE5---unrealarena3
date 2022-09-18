// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Components/UA3RespawnComponent.h"
#include "UA3_GameModeBase.h"

UUA3RespawnComponent::UUA3RespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUA3RespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld())
        return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UUA3RespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UUA3RespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UUA3RespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld())
            return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<AUA3_GameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
