// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/UA3AIController.h"
#include "AI/UA3CharacterAI.h"
#include "Components/UA3AIPerceptionComponent.h"
#include "Components/UA3RespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AUA3AIController::AUA3AIController()
{
    UA3AIPerceptionComponent = CreateDefaultSubobject<UUA3AIPerceptionComponent>("UA3PerceptionComponent");
    SetPerceptionComponent(*UA3AIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<UUA3RespawnComponent>("RespawnComponent");

    bWantsPlayerState = true;
}

void AUA3AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto UA3Character = Cast<AUA3CharacterAI>(InPawn))
    {
        RunBehaviorTree(UA3Character->BehaviorTreeAsset);
    }
}

void AUA3AIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SetFocus(GetFocusOnActor());
}

AActor* AUA3AIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
