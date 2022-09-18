// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/Services/UA3ChangeWeaponService.h"
#include "Components/UA3WeaponComponent.h"
#include "AIController.h"
#include "UA3Utils.h"

UUA3ChangeWeaponService::UUA3ChangeWeaponService()
{

    NodeName = "Change Weapon";
}

void UUA3ChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0&& FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
