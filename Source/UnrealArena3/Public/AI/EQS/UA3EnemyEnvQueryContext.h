// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "UA3EnemyEnvQueryContext.generated.h"

/**
 *
 */
UCLASS()
class UNREALARENA3_API UUA3EnemyEnvQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()

public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
