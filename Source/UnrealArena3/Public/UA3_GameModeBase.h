// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UA3CoreTypes.h"
#include "UA3_GameModeBase.generated.h"

class AAIController;
class USoundCue;

UCLASS()
class UNREALARENA3_API AUA3_GameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AUA3_GameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimConroller);

    FGameData GetGameData() const { return GameData; }
    int32 GetCurrentRoundNum() const { return CurrentRound; }
    int32 GetRoundSecondsRemaining() const { return RoundCountDown; }

    void RespawnRequest(AController* Controller);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void UpdateKillCounter(int32 KillsNum);


protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FGameData GameData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TArray<FString> BotNames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartMatchSound;

private:
    EUA3MatchState MatchState = EUA3MatchState::WaitingToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    int32 KillCounter = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();
    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController* Controller);

    void LogPlayerInfo();
    void StartRespawn(AController* Controller);

    void GameOver();
    void SetMatchState(EUA3MatchState State);
    void StopAllFire();
};
