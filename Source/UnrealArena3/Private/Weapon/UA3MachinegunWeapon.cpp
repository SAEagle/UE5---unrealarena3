// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Weapon/UA3MachinegunWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/UA3WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

AUA3MachinegunWeapon::AUA3MachinegunWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UUA3WeaponFXComponent>("WeaponFXComponent");
}

void AUA3MachinegunWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void AUA3MachinegunWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AUA3MachinegunWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void AUA3MachinegunWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void AUA3MachinegunWeapon::MakeShot()
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
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);

        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
    DecreaseAmmo();
}

bool AUA3MachinegunWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
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

void AUA3MachinegunWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void AUA3MachinegunWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if (!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }

    SetFXActive(true);
}

void AUA3MachinegunWeapon::SetFXActive(bool IsActive)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if (FireAudioComponent)
    {
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    }
}

void AUA3MachinegunWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* AUA3MachinegunWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void AUA3MachinegunWeapon::Zoom(bool Enabled)
{
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    if (Enabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }

    Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}
