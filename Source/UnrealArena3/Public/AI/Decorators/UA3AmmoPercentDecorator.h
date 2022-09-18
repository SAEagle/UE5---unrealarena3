// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UA3AmmoPercentDecorator.generated.h"

class AUA3BaseWeapon;

UCLASS()
class UNREALARENA3_API UUA3AmmoPercentDecorator : public UBTDecorator
{
    GENERATED_BODY()
public:
    UUA3AmmoPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AUA3BaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};