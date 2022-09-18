// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UA3AIController.generated.h"

class UUA3AIPerceptionComponent;
class UUA3RespawnComponent;

UCLASS()
class UNREALARENA3_API AUA3AIController : public AAIController
{
    GENERATED_BODY()

public:
    AUA3AIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUA3AIPerceptionComponent* UA3AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUA3RespawnComponent* RespawnComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

private:
    AActor* GetFocusOnActor() const;
};
