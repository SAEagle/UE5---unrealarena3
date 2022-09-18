// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/Services/UA3FireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "UA3Utils.h"

UUA3FireService::UUA3FireService()
{
    NodeName = "Fire";
}

void UUA3FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

     if (const auto Controller = OwnerComp.GetAIOwner())
      {
          if (const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(Controller->GetPawn()))
          {
              HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
          }
      }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}