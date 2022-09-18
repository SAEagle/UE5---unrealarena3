// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UA3BaseWidget.generated.h"

class USoundCue;

UCLASS()
class UNREALARENA3_API UUA3BaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* OpenSound;
};
