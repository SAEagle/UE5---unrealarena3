// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Weapon/UA3BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraComponent.h"
#include "../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AUA3BaseWeapon::AUA3BaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AUA3BaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
}

void AUA3BaseWeapon::StartFire() {}

void AUA3BaseWeapon::StopFire() {}

void AUA3BaseWeapon::MakeShot() {}

bool AUA3BaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto UA3Character = Cast<ACharacter>(GetOwner());
    if (!UA3Character)
        return false;

    if (UA3Character->IsPlayerControlled())
    {
        const auto Controller = UA3Character->GetController<APlayerController>();
        if (!Controller)
            return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
    return true;
}

FVector AUA3BaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AUA3BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{

    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation; // SocketTransform.GetLocation();

    const FVector ShootDirection = ViewRotation.Vector(); // SocketTransform.GetRotation().GetForwardVector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AUA3BaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
        return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.bReturnPhysicalMaterial = true;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AUA3BaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("No more bullets"));
        StopFire();
        return;
    }
    CurrentAmmo.Bullets--;

    if (/** IsClipEmpty() && */ IsClipEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool AUA3BaseWeapon::IsAmmoEmpty() const //adding clips in future for magazines check
{
    return !CurrentAmmo.Infinite; //&& CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AUA3BaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool AUA3BaseWeapon::IsAmmoFull() const //adding clips in future for magazines check
{
    return CurrentAmmo.Bullets >= 10;
}

void AUA3BaseWeapon::ChangeClip() //adding clips in future for magazines check
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            //UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    // CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool AUA3BaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    CurrentAmmo.Bullets += ClipsAmount;
    //UE_LOG(LogBaseWeapon, Warning, TEXT("Bullets were empty!"));
    return true;
}

bool AUA3BaseWeapon::IsVisible(bool Value)
{
    IsWeaponVisible = Value;
    return IsWeaponVisible;
}

void AUA3BaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/ ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

UNiagaraComponent* AUA3BaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(
        MuzzleFX, WeaponMesh, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}
