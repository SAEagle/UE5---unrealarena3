// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3BaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UUA3BaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
