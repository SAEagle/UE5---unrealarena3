// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Menu/UA3MenuPlayerController.h"
#include "UA3GameInstance.h"

void AUA3MenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
