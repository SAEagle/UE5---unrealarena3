// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "UI/UA3BaseWidget.h"
#include "UA3PauseWidget.generated.h"

class UButton;

UCLASS()
class UNREALARENA3_API UUA3PauseWidget : public UUA3BaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
};
