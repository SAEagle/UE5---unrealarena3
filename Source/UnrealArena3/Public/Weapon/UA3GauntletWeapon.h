// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Weapon/UA3BaseWeapon.h"
#include "UA3GauntletWeapon.generated.h"

class UUA3WeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class UNREALARENA3_API AUA3GauntletWeapon : public AUA3BaseWeapon
{
    GENERATED_BODY()

public:
    AUA3GauntletWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

    void InitFX();

    void SetFXActive(bool IsActive);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UUA3WeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void MakeDamage(const FHitResult& HitResult);
    AController* GetController() const;
};
