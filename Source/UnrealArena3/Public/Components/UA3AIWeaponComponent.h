// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Components/UA3WeaponComponent.h"
#include "UA3AIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class UNREALARENA3_API UUA3AIWeaponComponent : public UUA3WeaponComponent
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
