// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "UA3CoreTypes.h"
#include "UI/UA3BaseWidget.h"
#include "UA3GameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class UNREALARENA3_API UUA3GameOverWidget : public UUA3BaseWidget
{
    GENERATED_BODY()

public:

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(EUA3MatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
