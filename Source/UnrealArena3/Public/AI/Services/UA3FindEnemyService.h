// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UA3FindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class UNREALARENA3_API UUA3FindEnemyService : public UBTService
{
    GENERATED_BODY()

public:
    UUA3FindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
