// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "UA3CoreTypes.h"
#include "UI/UA3BaseWidget.h"
#include "UA3MenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UUA3GameInstance;
class UUA3LevelItemWidget;
class USoundCue;

UCLASS()
class UNREALARENA3_API UUA3MenuWidget : public UUA3BaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;

    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UPROPERTY()
    TArray<UUA3LevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    UUA3GameInstance* GetUA3GameInstance() const;
};
