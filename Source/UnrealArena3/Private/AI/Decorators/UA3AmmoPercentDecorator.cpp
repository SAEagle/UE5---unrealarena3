// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/Decorators/UA3AmmoPercentDecorator.h"
#include "AIController.h"
#include "UA3Utils.h"
#include "Components/UA3WeaponComponent.h"

UUA3AmmoPercentDecorator::UUA3AmmoPercentDecorator()
{

    NodeName = "Ammo Percent";
}

bool UUA3AmmoPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
