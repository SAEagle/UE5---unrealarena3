// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Player/UA3PlayerController.h"
#include "Components/UA3RespawnComponent.h"
#include "UA3_GameModeBase.h"
#include "UA3GameInstance.h"

AUA3PlayerController::AUA3PlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UUA3RespawnComponent>("RespawnComponent");
}

void AUA3PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        if (const auto GameMode = Cast<AUA3_GameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AUA3PlayerController::OnMatchStateChanged);
        }
    }
}

void AUA3PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void AUA3PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent)
        return;

    InputComponent->BindAction("Pause", IE_Pressed, this, &AUA3PlayerController::OnPauseGame);
    InputComponent->BindAction("Mute", IE_Pressed, this, &AUA3PlayerController::OnMuteSound);
}

void AUA3PlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AUA3PlayerController::OnMatchStateChanged(EUA3MatchState State)
{
    if (State == EUA3MatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void AUA3PlayerController::OnMuteSound()
{
    if (!GetWorld())
        return;

    const auto UA3GameInstance = GetWorld()->GetGameInstance<UUA3GameInstance>();
    if (!UA3GameInstance)
        return;

    UA3GameInstance->ToggleVolume();
}
