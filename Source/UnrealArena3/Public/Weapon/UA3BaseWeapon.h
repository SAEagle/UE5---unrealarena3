// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UA3CoreTypes.h"
#include "UA3BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class UNREALARENA3_API AUA3BaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    AUA3BaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire(); // virtual due to having the inherited classes and components using this function later

    void ChangeClip();
    // bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }

    bool GetWeaponUIVisibility() const { return IsWeaponVisible; }
    void SetWeaponUIVisibility(const bool Value) { IsWeaponVisible = Value; }

    bool TryToAddAmmo(int32 ClipsAmount);
    bool IsVisible(bool Value);
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;
    bool IsClipEmpty() const;

    virtual void Zoom(bool Enabled) {}

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    bool IsWeaponVisible = false;

    virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStar, FVector& TraceEnd) const;

    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    void DecreaseAmmo();

    void LogAmmo();

    UNiagaraComponent* SpawnMuzzleFX();

private:
    FAmmoData CurrentAmmo;
};
