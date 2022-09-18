// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UA3CoreTypes.h"
#include "UA3PlayerController.generated.h"

class UUA3RespawnComponent;

UCLASS()
class UNREALARENA3_API AUA3PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AUA3PlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUA3RespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(EUA3MatchState State);
    void OnMuteSound();
};
