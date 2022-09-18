// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3GoToMenuWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UA3GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogGoToMenuWidget, All, All);

void UUA3GoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &UUA3GoToMenuWidget::GoToMenu);
    }
}

void UUA3GoToMenuWidget::GoToMenu()
{

    if (!GetWorld())
        return;

    const auto UA3GameInstance = GetWorld()->GetGameInstance<UUA3GameInstance>();
    if (!UA3GameInstance)
        return;

    if (UA3GameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Menu Level name is not defined"));
        return;
    }

    const FName MenuLevelName = "MenuLevel";
    UGameplayStatics::OpenLevel(this, UA3GameInstance->GetMenuLevelName());
}
