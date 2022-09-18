// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Weapon/UA3BaseWeapon.h"
#include "UA3ShotgunWeapon.generated.h"

class UUA3WeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class UNREALARENA3_API AUA3ShotgunWeapon : public AUA3BaseWeapon
{
    GENERATED_BODY()

public:
    AUA3ShotgunWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

    void CanFire();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    int32 BulletsAmmount = 11;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UUA3WeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStar, FVector& TraceEnd) const override;

private:
    bool IsCanFire = true;
    FTimerHandle ShotTimerHandle;
    FTimerHandle CanFireTimer;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void MakeDamage(const FHitResult& HitResult);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

    AController* GetController() const;
};
