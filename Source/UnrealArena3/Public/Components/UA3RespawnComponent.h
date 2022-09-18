// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UA3RespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARENA3_API UUA3RespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUA3RespawnComponent();

    void Respawn(int32 RespawnTime);
    int32 GetRespawnCountDown() const { return RespawnCountDown; }
    bool IsRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;

    void RespawnTimerUpdate();
};
