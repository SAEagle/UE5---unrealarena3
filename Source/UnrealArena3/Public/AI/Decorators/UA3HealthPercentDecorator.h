// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UA3HealthPercentDecorator.generated.h"

/**
 *
 */
UCLASS()
class UNREALARENA3_API UUA3HealthPercentDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    UUA3HealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
