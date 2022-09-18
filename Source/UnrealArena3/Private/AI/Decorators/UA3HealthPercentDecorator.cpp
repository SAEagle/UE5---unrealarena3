// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/Decorators/UA3HealthPercentDecorator.h"
#include "AIController.h"
#include "UA3Utils.h"
#include "Components/UA3HealthComponent.h"

UUA3HealthPercentDecorator::UUA3HealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool UUA3HealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
