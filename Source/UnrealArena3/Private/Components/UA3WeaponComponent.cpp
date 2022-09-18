// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Components/UA3WeaponComponent.h"
#include "Weapon/UA3BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/UA3EquipFinishedAnimNotify.h"
#include "Animations/UA3ReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// constexpr static int32 WeaponNum = 2;

UUA3WeaponComponent::UUA3WeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUA3WeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentWeaponIndex = 1;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
    Weapons[CurrentWeaponIndex]->SetWeaponUIVisibility(true);
}

void UUA3WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UUA3WeaponComponent::OnDeathCall()
{
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
}

void UUA3WeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<AUA3BaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon)
            continue;
        Weapon->OnClipEmpty.AddUObject(this, &UUA3WeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        Weapon->IsVisible(false);
        Weapon->SetActorHiddenInGame(true);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UUA3WeaponComponent::StartFire()
{
    if (!CanFire())
        return;
    if (CurrentWeapon->IsClipEmpty() && CurrentWeaponIndex != 0)
    {
        NextWeapon();
    }

    CurrentWeapon->StartFire();
}

void UUA3WeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

void UUA3WeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;
    CurrentWeapon->StopFire();
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        if (Weapons[NextIndex]->GetWeaponUIVisibility() && !Weapons[NextIndex]->IsClipEmpty())
            break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        if (Weapons[NextIndex]->GetWeaponUIVisibility())
        {
            CurrentWeaponIndex = NextIndex;
            EquipWeapon(CurrentWeaponIndex);
        }
        return;
    }
}

void UUA3WeaponComponent::PrevWeapon()
{
    if (!CanEquip())
        return;
    CurrentWeapon->StopFire();
    int32 PrevIndex = (CurrentWeaponIndex - 1) % Weapons.Num();

    if (PrevIndex == 0)
        return;
    while (PrevIndex != CurrentWeaponIndex)
    {
        if (Weapons[PrevIndex]->GetWeaponUIVisibility() && !Weapons[PrevIndex]->IsClipEmpty())
            break;
        PrevIndex = (PrevIndex - 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != PrevIndex)
    {
        if (Weapons[PrevIndex]->GetWeaponUIVisibility())
        {
            CurrentWeaponIndex = PrevIndex;
            EquipWeapon(CurrentWeaponIndex);
        }
        return;
    }
}

void UUA3WeaponComponent::Reload()
{
    // ChangeClip(); In case of implementing mags
}

void UUA3WeaponComponent::EquipWeapon1()
{
    CurrentWeaponIndex = 0;
    EquipWeapon(0);
}

void UUA3WeaponComponent::EquipWeapon2()
{
    if (!Weapons[1]->IsClipEmpty())
    {
        CurrentWeaponIndex = 1;
        EquipWeapon(1);
    }
}

void UUA3WeaponComponent::EquipWeapon3()
{
    if (!Weapons[2]->IsClipEmpty() && Weapons[2]->GetWeaponUIVisibility())
    {
        CurrentWeaponIndex = 2;
        EquipWeapon(2);
    }
}

void UUA3WeaponComponent::EquipWeapon5()
{
    if (!Weapons[3]->IsClipEmpty() && Weapons[3]->GetWeaponUIVisibility())
    {
        CurrentWeaponIndex = 3;
        EquipWeapon(3);
    }
}

void UUA3WeaponComponent::EquipWeapon8()
{
    if (!Weapons[4]->IsClipEmpty() && Weapons[4]->GetWeaponUIVisibility())
    {
        CurrentWeaponIndex = 4;
        EquipWeapon(4);
    }
}

bool UUA3WeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool UUA3WeaponComponent::GetWeaponUIData(int32 Index, FWeaponUIData& UIData) const
{
    if (Weapons.Num() != 0)
    {
        const auto WeaponIndex = Weapons[Index];
        UIData = WeaponIndex->GetUIData();
        return true;
    }
    return false;
}

bool UUA3WeaponComponent::GetWeaponAmmoData(int32 Index, FAmmoData& AmmoData) const
{
    if (Weapons.Num() != 0)
    {
        const auto WeaponIndex = Weapons[Index];
        AmmoData = WeaponIndex->GetAmmoData();
        return true;
    }
    return false;
}

bool UUA3WeaponComponent::GetWeaponUIVisibility(int32 Index, bool Value) const
{
    if (Weapons.Num() != 0)
    {
        const auto WeaponIndex = Weapons[Index];
        if (Value == WeaponIndex->GetWeaponUIVisibility())
            return true;
    }
    return false;
}

bool UUA3WeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}

bool UUA3WeaponComponent::GetCurrentWeaponIndex(int32 Index) const
{
    if (CurrentWeapon)
    {
        if (Index == CurrentWeaponIndex)
            return true;
    }
    return false;
}

bool UUA3WeaponComponent::TryToAddAmmo(TSubclassOf<AUA3BaseWeapon> WeaponType, int32 ClipsAmount)
{
    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}

bool UUA3WeaponComponent::TryToAddAmmoFirstTime(TSubclassOf<AUA3BaseWeapon> WeaponType, int32 ClipsAmount)
{
    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            Weapon->SetWeaponUIVisibility(true);
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}

bool UUA3WeaponComponent::NeedAmmo(TSubclassOf<AUA3BaseWeapon> WeaponType)
{
    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return !Weapon->IsAmmoFull();
        }
    }
    return false;
}

void UUA3WeaponComponent::AttachWeaponToSocket(AUA3BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent)
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UUA3WeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid"));
        return;
    }
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        CurrentWeapon->SetActorHiddenInGame(true);
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate(
        [&](const FWeaponData& Data) //
        {
            return Data.WeaponClass == CurrentWeapon->GetClass(); //
        });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    CurrentWeapon->SetActorHiddenInGame(false);
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquiAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
    CurrentWeapon->StopFire();
}

bool UUA3WeaponComponent::AddWeaponToCharacter(bool Value)
{
    return false;
}

void UUA3WeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    Character->PlayAnimMontage(Animation);
}

void UUA3WeaponComponent::InitAnimations()
{
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UUA3EquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UUA3WeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip animmontage notify is forgotten to set "));
        checkNoEntry();
    }

    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UUA3ReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload animmontage notify is forgotten to set "));
            checkNoEntry();
        }
        ReloadFinishedNotify->OnNotified.AddUObject(this, &UUA3WeaponComponent::OnReloadFinished);
    }
}

void UUA3WeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh())
        return;

    EquiAnimInProgress = false;
}

void UUA3WeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh())
        return;

    ReloadAnimInProgress = false;
}

bool UUA3WeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquiAnimInProgress && !ReloadAnimInProgress;
}

bool UUA3WeaponComponent::CanEquip() const
{
    return !EquiAnimInProgress;
}

bool UUA3WeaponComponent::CanReload() const
{
    return CurrentWeapon          //
           && !EquiAnimInProgress //
           && !ReloadAnimInProgress;
}

// magazines logic
void UUA3WeaponComponent::OnEmptyClip(AUA3BaseWeapon* AmmoEmptyWeapon)
{
    if (!AmmoEmptyWeapon)
        return;
    if (CurrentWeapon == AmmoEmptyWeapon)
    {
        // ChangeClip(); No Ammo Debug
    }
    else
    {
        for (const auto Weapon : Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
            {
                // Weapon->ChangeClip(); No Ammo Debug
            }
        }
    }
}

void UUA3WeaponComponent::ChangeClip()
{
    if (!CanReload())
        return;
    CurrentWeapon->StopFire();
    // CurrentWeapon->ChangeClip();
    // ReloadAnimInProgress = true;
    //  PlayAnimMontage(CurrentReloadAnimMontage);
}
