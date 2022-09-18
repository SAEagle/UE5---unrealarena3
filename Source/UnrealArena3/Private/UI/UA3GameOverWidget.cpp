// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3GameOverWidget.h"
#include "UA3_GameModeBase.h"
#include "Player/UA3PlayerState.h"
#include "UA3PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "UA3Utils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogReset, All, All);

void UUA3GameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<AUA3_GameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UUA3GameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UUA3GameOverWidget::OnResetLevel);
    }
}

void UUA3GameOverWidget::OnMatchStateChanged(EUA3MatchState State)
{
    if (State == EUA3MatchState::GameOver)
    {
        UpdatePlayerStat();
    }
}

void UUA3GameOverWidget::UpdatePlayerStat()
{
    if (!GetWorld() || !PlayerStatBox)
        return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<AUA3PlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        const auto PlayerStateRowWidget = CreateWidget<UUA3PlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStateRowWidget)
            continue;

        PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStateRowWidget->SetKills(UA3Utils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStateRowWidget->SetDeaths(UA3Utils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStateRowWidget->SetTeam(UA3Utils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStateRowWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStateRowWidget);
    }
}

void UUA3GameOverWidget::OnResetLevel()
{
    // const FName CurrentLevelName = "TestLevel";
    const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
