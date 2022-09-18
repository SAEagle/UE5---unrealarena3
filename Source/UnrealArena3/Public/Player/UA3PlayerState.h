// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "UA3PlayerState.generated.h"

UCLASS()
class UNREALARENA3_API AUA3PlayerState : public APlayerState
{
    GENERATED_BODY()
public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKill() { ++KillsNum; }
    int32 GetKillsNum() const { return KillsNum; }

    void AddDeath() { ++DeathsNum; }
    int32 GetDeathsNum() const { return DeathsNum; }

    void LogInfo();

private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
