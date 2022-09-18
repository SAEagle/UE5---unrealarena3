// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development
#include "AI/Tasks/UA3_NextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UUA3_NextLocationTask::UUA3_NextLocationTask()
{
    NodeName = "Next Location";
}

EBTNodeResult::Type UUA3_NextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
        return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return EBTNodeResult::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys)
        return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    auto Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor)
            return EBTNodeResult::Failed;
        Location = CenterActor->GetActorLocation();
    }

    const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
    if (!Found)
        return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
    return EBTNodeResult::Succeeded;
}
