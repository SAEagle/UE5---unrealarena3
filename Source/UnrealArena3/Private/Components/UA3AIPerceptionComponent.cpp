// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Components/UA3AIPerceptionComponent.h"
#include "AIController.h"
#include "UA3Utils.h"
#include "Components/UA3HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* UUA3AIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if (PercieveActors.Num() == 0)
            return nullptr;
    }

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(PercieveActor);

        const auto PercievePAwn = Cast<APawn>(PercieveActor);
        const auto AreEnemies = PercievePAwn && UA3Utils::AreEnemies(Controller, PercievePAwn->Controller);

        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies) //TODO check if in the same team or not
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }

    return BestPawn;
}
