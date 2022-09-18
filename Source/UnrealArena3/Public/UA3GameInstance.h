// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UA3CoreTypes.h"
#include "UA3GameInstance.generated.h"

class USoundClass;

UCLASS()
class UNREALARENA3_API UUA3GameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FLevelData GetStartupLevelData() const { return StartupLevel; }
    void SetStartupLevelData(const FLevelData& Data) { StartupLevel = Data; }

    TArray<FLevelData> GetLevelsData() const { return LevelsData; }

    FName GetMenuLevelName() const { return MenuLevelName; }

    void ToggleVolume();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    FLevelData StartupLevel;
};
