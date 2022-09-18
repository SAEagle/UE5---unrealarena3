// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UA3PlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class UNREALARENA3_API UUA3PlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);
    void SetTeamColor(const FLinearColor& Color);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;

    UPROPERTY(meta = (BindWidget))
    UImage* TeamImage;
};
