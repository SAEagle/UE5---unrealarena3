// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UA3Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UUA3WeaponFXComponent;
class UStaticMesh;

UCLASS()
class UNREALARENA3_API AUA3Projectile : public AActor
{
    GENERATED_BODY()

public:
    AUA3Projectile();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; };

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UUA3WeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float RadialImpulse = 5.0f; //add physics to rockets

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.0f;

    virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    AController* GetController() const;
};