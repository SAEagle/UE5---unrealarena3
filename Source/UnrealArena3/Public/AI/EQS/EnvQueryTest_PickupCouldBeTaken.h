// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class UNREALARENA3_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
    GENERATED_BODY()
public:
    UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
