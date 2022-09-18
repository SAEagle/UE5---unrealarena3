// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development


#include "Player/UA3PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogUA3PlayerState, All, All);

void AUA3PlayerState::LogInfo() {
    UE_LOG(LogUA3PlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
