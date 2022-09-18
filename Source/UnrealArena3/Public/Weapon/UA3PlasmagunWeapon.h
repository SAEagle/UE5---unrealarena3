// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Weapon/UA3BaseWeapon.h"
#include "UA3PlasmagunWeapon.generated.h"

class AUA3Projectile;
class USoundCue;

UCLASS()
class UNREALARENA3_API AUA3PlasmagunWeapon : public AUA3BaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;

    void CanFire();

    void StopFire();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AUA3Projectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;

    virtual void MakeShot() override;

private:
    bool IsCanFire = true;
    FTimerHandle ShotTimerHandle;
    FTimerHandle CanFireTimer;
};
