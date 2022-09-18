// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Menu/UA3MenuGameModeBase.h"
#include "Menu/UA3MenuPlayerController.h"
#include "Menu/UI/UA3MenuHUD.h"

AUA3MenuGameModeBase::AUA3MenuGameModeBase()
{
    PlayerControllerClass = AUA3MenuPlayerController::StaticClass();
    HUDClass = AUA3MenuHUD::StaticClass();
}
