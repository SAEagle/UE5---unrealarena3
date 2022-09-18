// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Menu/UI/UA3MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UA3GameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/UA3LevelItemWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

void UUA3MenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UUA3MenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UUA3MenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void UUA3MenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation != HideAnimation)
        return;
    const auto UA3GameInstance = GetWorld()->GetGameInstance<UUA3GameInstance>();
    if (!UA3GameInstance)
        return;

    if (UA3GameInstance->GetStartupLevelData().LevelName.IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Level name is NONE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, UA3GameInstance->GetStartupLevelData().LevelName);
}

void UUA3MenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UUA3MenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UUA3MenuWidget::InitLevelItems()
{
    const auto UA3GameInstance = GetUA3GameInstance();
    if (!UA3GameInstance)
        return;

    checkf(UA3GameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemBox)
        return;
    LevelItemBox->ClearChildren();
    UE_LOG(LogMenuWidget, Warning, TEXT("LevelWidgetCreated is not defined"));

    for (auto LevelData : UA3GameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<UUA3LevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget)
            continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UUA3MenuWidget::OnLevelSelected);

        LevelItemBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
        UE_LOG(LogMenuWidget, Warning, TEXT("LevelWidgetCreated"));
    }

    if (UA3GameInstance->GetStartupLevelData().LevelName.IsNone())
    {
        OnLevelSelected(UA3GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(UA3GameInstance->GetStartupLevelData());
    }
}

void UUA3MenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto UA3GameInstance = GetUA3GameInstance();
    if (!UA3GameInstance)
        return;

    UA3GameInstance->SetStartupLevelData(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

UUA3GameInstance* UUA3MenuWidget::GetUA3GameInstance() const
{
    if (!GetWorld())
        return nullptr;
    return GetWorld()->GetGameInstance<UUA3GameInstance>();
}
