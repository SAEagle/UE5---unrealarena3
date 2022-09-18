// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development
#include "Weapon/UA3ShotgunWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/UA3WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogShotgunWeapon, All, All);
AUA3ShotgunWeapon::AUA3ShotgunWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UUA3WeaponFXComponent>("WeaponFXComponent");
}

void AUA3ShotgunWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void AUA3ShotgunWeapon::StartFire()
{
    if (!IsCanFire)
    {
        UE_LOG(LogShotgunWeapon, Display, TEXT("Shotgun can't fire"))
    }
    if (IsCanFire)
    {
        GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AUA3ShotgunWeapon::MakeShot, TimeBetweenShots, true);
        MakeShot();
    }
}

void AUA3ShotgunWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AUA3ShotgunWeapon::CanFire()
{
    if (GetWorldTimerManager().IsTimerActive(CanFireTimer))
    {
        IsCanFire = false;
    }
    IsCanFire = true;
}

void AUA3ShotgunWeapon::MakeShot()
{
    if (!GetWorld() || IsClipEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;

    for (int i = 0; i < BulletsAmmount; i++)
    {
        GetTraceData(TraceStart, TraceEnd);
        MakeHit(HitResult, TraceStart, TraceEnd);
        FVector TraceFXEnd = TraceEnd;
        if (HitResult.bBlockingHit)
        {
            TraceFXEnd = HitResult.ImpactPoint;
            MakeDamage(HitResult);
            WeaponFXComponent->PlayImpactFX(HitResult);
        }
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    GetWorldTimerManager().SetTimer(CanFireTimer, this, &AUA3ShotgunWeapon::CanFire, (TimeBetweenShots - 0.3f), false);
    IsCanFire = false;
}

bool AUA3ShotgunWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation; // SocketTransform.GetLocation();

    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad); // SocketTransform.GetRotation().GetForwardVector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AUA3ShotgunWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void AUA3ShotgunWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* AUA3ShotgunWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}