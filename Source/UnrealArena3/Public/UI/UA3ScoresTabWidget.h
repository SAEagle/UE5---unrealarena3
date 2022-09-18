// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "UI/UA3BaseWidget.h"
#include "UA3ScoresTabWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class UNREALARENA3_API UUA3ScoresTabWidget : public UUA3BaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void Show();

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    virtual void NativeOnInitialized() override;

    void OnMatchStateChanged(EUA3MatchState State);

private:
    void UpdateScoresTabStat();
};
