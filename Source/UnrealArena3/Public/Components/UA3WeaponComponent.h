// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UA3CoreTypes.h"
#include "UA3WeaponComponent.generated.h"

class AUA3BaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARENA3_API UUA3WeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UUA3WeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void PrevWeapon();
    void Reload();
    void OnDeathCall();

    void EquipWeapon1();
    void EquipWeapon2();
    void EquipWeapon3();
    void EquipWeapon5();
    void EquipWeapon8();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetWeaponUIData(int32 Index, FWeaponUIData& UIData) const;
    bool GetWeaponAmmoData(int32 Index, FAmmoData& AmmoData) const;
    bool GetWeaponUIVisibility(int32 Index, bool Value) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "DeathFX")
    bool GetCurrentWeaponIndex(int32 Index) const;

    bool TryToAddAmmo(TSubclassOf<AUA3BaseWeapon> WeaponType, int32 ClipsAmount);
    bool TryToAddAmmoFirstTime(TSubclassOf<AUA3BaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<AUA3BaseWeapon> WeaponType);
    bool AddWeaponToCharacter(bool Value);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY() // EVERY UObject should be marked with property otherwise garbage collector can have some issues
    AUA3BaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AUA3BaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;

    void EquipWeapon(int32 WeaponIndex);

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquiAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AUA3BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

    void PlayAnimMontage(UAnimMontage* Animation);

    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanReload() const;

    void OnEmptyClip(AUA3BaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
};
