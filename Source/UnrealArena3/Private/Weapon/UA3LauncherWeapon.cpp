// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Weapon/UA3LauncherWeapon.h"
#include "Weapon/UA3Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogLauncherWeapon, All, All);

void AUA3LauncherWeapon::StartFire()
{
    if (!IsCanFire)
    {
        UE_LOG(LogLauncherWeapon, Display, TEXT("Launcher can't fire"))
    }
    if (IsCanFire)
    {
        GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AUA3LauncherWeapon::MakeShot, TimeBetweenShots, true);
        MakeShot();
    }
}

void AUA3LauncherWeapon::CanFire()
{
    if (GetWorldTimerManager().IsTimerActive(CanFireTimer))
    {
        IsCanFire = false;
    }
    IsCanFire = true;
}

void AUA3LauncherWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AUA3LauncherWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    if (IsClipEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AUA3Projectile* Projectile = GetWorld()->SpawnActorDeferred<AUA3Projectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    GetWorldTimerManager().SetTimer(CanFireTimer, this, &AUA3LauncherWeapon::CanFire, (TimeBetweenShots - 0.5f), false);
    IsCanFire = false;
}
