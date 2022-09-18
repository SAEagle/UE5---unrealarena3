// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"

void UUA3PauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UUA3PauseWidget::OnClearPause);
    }
}

void UUA3PauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}
