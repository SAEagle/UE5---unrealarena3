// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Menu/UI/UA3LevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUA3LevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &UUA3LevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &UUA3LevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &UUA3LevelItemWidget::OnLevelItemUnhovered);
    }
}

void UUA3LevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void UUA3LevelItemWidget::OnLevelItemHovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void UUA3LevelItemWidget::OnLevelItemUnhovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UUA3LevelItemWidget::SetLevelData(const FLevelData& Data)
{

    LevelData = Data;

    if (LevelNameTextButton)
    {
        LevelNameTextButton->SetText(FText::FromName(Data.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void UUA3LevelItemWidget::SetSelected(bool IsSelected)
{
    if (LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}
