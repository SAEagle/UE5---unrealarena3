// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Weapon/UA3GauntletWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/UA3WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

AUA3GauntletWeapon::AUA3GauntletWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UUA3WeaponFXComponent>("WeaponFXComponent");
}

void AUA3GauntletWeapon::BeginPlay()
{
    Super::BeginPlay();
    // additonal fx here
}

void AUA3GauntletWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AUA3GauntletWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void AUA3GauntletWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void AUA3GauntletWeapon::InitFX()
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

void AUA3GauntletWeapon::SetFXActive(bool IsActive)
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

void AUA3GauntletWeapon::MakeShot()
{
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
    }
}

void AUA3GauntletWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

AController* AUA3GauntletWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
