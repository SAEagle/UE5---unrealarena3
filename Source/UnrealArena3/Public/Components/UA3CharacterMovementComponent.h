// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UA3CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALARENA3_API UUA3CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta =(ClampMin = "1.5", ClampMax = "10.0"))
      float RunModifier = 2.0f;
      virtual float GetMaxSpeed() const override;
	
};
