// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Player/UA3BaseCharacter.h"
#include "UA3CharacterAI.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class UNREALARENA3_API AUA3CharacterAI : public AUA3BaseCharacter
{
    GENERATED_BODY()

public:
    AUA3CharacterAI(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.0f;

    virtual void BeginPlay() override;

    virtual void OnDeath() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
    void UpdateHealthWidgetVisibility();
};
