// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/Services/UA3FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "UA3Utils.h"
#include "Components/UA3AIPerceptionComponent.h"

UUA3FindEnemyService::UUA3FindEnemyService()
{
    NodeName = "Find Enemy";
}

void UUA3FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = UA3Utils::GetUA3PlayerComponent<UUA3AIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}