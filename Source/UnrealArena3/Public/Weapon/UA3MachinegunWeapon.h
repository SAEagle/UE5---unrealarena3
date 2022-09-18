// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Weapon/UA3BaseWeapon.h"
#include "UA3MachinegunWeapon.generated.h"

class UUA3WeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class UNREALARENA3_API AUA3MachinegunWeapon : public AUA3BaseWeapon
{
    GENERATED_BODY()
public:
    AUA3MachinegunWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Zoom(bool Enabled) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoomAngle = 50.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UUA3WeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStar, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void MakeDamage(const FHitResult& HitResult);
    void InitFX();
    void SetFXActive(bool IsActive);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

    AController* GetController() const;

    float DefaultCameraFOV = 90.0f;
};
