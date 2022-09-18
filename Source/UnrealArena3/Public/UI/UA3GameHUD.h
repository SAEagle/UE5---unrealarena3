// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UA3CoreTypes.h"
#include "UA3GameHUD.generated.h"

class UUA3BaseWidget;

UCLASS()
class UNREALARENA3_API AUA3GameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

public:
    virtual void DrawHUD() override;

private:
    UPROPERTY()
    TMap<EUA3MatchState, UUA3BaseWidget*> GameWidgets;

    UPROPERTY()
    UUA3BaseWidget* CurrentWidget = nullptr;

    void DrawCrossHair();
    void OnMatchStateChanged(EUA3MatchState State);
};
