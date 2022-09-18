// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "UA3AIPerceptionComponent.generated.h"

/**
 *
 */
UCLASS()
class UNREALARENA3_API UUA3AIPerceptionComponent : public UAIPerceptionComponent
{
    GENERATED_BODY()

public:
    AActor* GetClosestEnemy() const;
};
