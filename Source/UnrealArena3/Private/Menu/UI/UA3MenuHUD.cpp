// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Menu/UI/UA3MenuHUD.h"
#include "UI/UA3BaseWidget.h"

void AUA3MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUA3BaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
