// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UA3GameDataWidget.generated.h"

class AUA3_GameModeBase;
class AUA3PlayerState;

UCLASS()
class UNREALARENA3_API UUA3GameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondsRemaining() const;

private:
    AUA3_GameModeBase* GetUA3GameMode() const;
    AUA3PlayerState* GetUA3PlayerState() const;
};
