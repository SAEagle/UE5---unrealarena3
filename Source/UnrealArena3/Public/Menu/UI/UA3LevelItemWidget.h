// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UA3CoreTypes.h"
#include "UA3LevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class UNREALARENA3_API UUA3LevelItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const { return LevelData; }

    void SetSelected(bool IsSelected);

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextButton;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelItemClicked();

    UFUNCTION()
    void OnLevelItemHovered();

    UFUNCTION()
    void OnLevelItemUnhovered();
};
