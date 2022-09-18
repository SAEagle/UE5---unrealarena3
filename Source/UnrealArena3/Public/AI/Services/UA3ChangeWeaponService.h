// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UA3ChangeWeaponService.generated.h"

/**
 *
 */
UCLASS()
class UNREALARENA3_API UUA3ChangeWeaponService : public UBTService
{
    GENERATED_BODY()

public:
    UUA3ChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
