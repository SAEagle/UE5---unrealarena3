// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UA3GoToMenuWidget.generated.h"

class UButton;

UCLASS()
class UNREALARENA3_API UUA3GoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void GoToMenu();
};
