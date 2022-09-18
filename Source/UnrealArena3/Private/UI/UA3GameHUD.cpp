// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3GameHUD.h"
#include "Engine/Canvas.h"
#include "UI/UA3BaseWidget.h"
#include "UA3_GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogUA3GameHUD, All, All);

void AUA3GameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EUA3MatchState::InProgress, CreateWidget<UUA3BaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EUA3MatchState::Pause, CreateWidget<UUA3BaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EUA3MatchState::GameOver, CreateWidget<UUA3BaseWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget)
            continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AUA3_GameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AUA3GameHUD::OnMatchStateChanged);
        }
    }
}

void AUA3GameHUD::DrawHUD()
{
    Super::DrawHUD();
    // DrawCrossHair();
}

void AUA3GameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void AUA3GameHUD::OnMatchStateChanged(EUA3MatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }

    UE_LOG(LogUA3GameHUD, Display, TEXT("Match state: %s"), *UEnum::GetValueAsString(State));
}
