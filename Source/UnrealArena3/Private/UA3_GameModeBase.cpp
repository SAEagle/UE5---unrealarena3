// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UA3_GameModeBase.h"
#include "Player/UA3BaseCharacter.h"
#include "Player/UA3PlayerController.h"
#include "UI/UA3GameHUD.h"
#include "AI/UA3AIController.h"
#include "Player/UA3PlayerState.h"
#include "UA3Utils.h"
#include "Components/UA3RespawnComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "EngineUtils.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogUA3GameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 5;

AUA3_GameModeBase::AUA3_GameModeBase()
{
    DefaultPawnClass = AUA3BaseCharacter::StaticClass();
    PlayerControllerClass = AUA3PlayerController::StaticClass();
    HUDClass = AUA3GameHUD::StaticClass();
    PlayerStateClass = AUA3PlayerState::StaticClass();
}

void AUA3_GameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    CurrentRound = 1;
    StartRound();
    UGameplayStatics::PlaySound2D(GetWorld(), StartMatchSound);

    SetMatchState(EUA3MatchState::InProgress);
}

UClass* AUA3_GameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AUA3_GameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto UA3AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(UA3AIController);
    }
}

void AUA3_GameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AUA3_GameModeBase::GameTimerUpdate, 1.0f, true);
}

void AUA3_GameModeBase::GameTimerUpdate()
{
    UE_LOG(LogUA3GameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void AUA3_GameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AUA3_GameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void AUA3_GameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<AUA3PlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Manny"); // BotNames[FMath::FRandRange(0, 4)]);
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AUA3_GameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    return GameData.DefaultTeamColor;
}

void AUA3_GameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller)
        return;

    const auto Character = Cast<AUA3BaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<AUA3PlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AUA3_GameModeBase::Killed(AController* KillerController, AController* VictimConroller)
{
    const auto KillerPlayerState = KillerController ? Cast<AUA3PlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = KillerController ? Cast<AUA3PlayerState>(VictimConroller->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimConroller);
}

void AUA3_GameModeBase::LogPlayerInfo()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<AUA3PlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->LogInfo();
    }
}

void AUA3_GameModeBase::StartRespawn(AController* Controller)
{
    if (KillCounter == GameData.RoundKillTarget)
    {
        UE_LOG(LogUA3GameModeBase, Display, TEXT("Trying to not Spawn Bot"));
        return;
    }

    const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvailable)
        return;

    const auto RespawnComponent = UA3Utils::GetUA3PlayerComponent<UUA3RespawnComponent>(Controller);
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void AUA3_GameModeBase::GameOver()
{
    UE_LOG(LogUA3GameModeBase, Display, TEXT("Game OVER"));
    LogPlayerInfo();

    GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    StopAllFire();
    SetMatchState(EUA3MatchState::GameOver);
}

void AUA3_GameModeBase::SetMatchState(EUA3MatchState State)
{
    if (MatchState == State)
        return;

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}

void AUA3_GameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

bool AUA3_GameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        StopAllFire();
        SetMatchState(EUA3MatchState::Pause);
    }
    return PauseSet;
}

bool AUA3_GameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(EUA3MatchState::InProgress);
    }
    return PauseCleared;
}

void AUA3_GameModeBase::StopAllFire()
{
    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(Pawn);
        if (!WeaponComponent)
            continue;
        WeaponComponent->StopFire();
    }
}

void AUA3_GameModeBase::UpdateKillCounter(int32 KillsNum)
{
    KillCounter = KillsNum;
    if (KillCounter == GameData.RoundKillTarget)
    {
        GameOver();
    }
}
