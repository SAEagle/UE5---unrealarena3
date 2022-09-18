// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Weapon/UA3Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/UA3WeaponFXComponent.h"

AUA3Projectile::AUA3Projectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<UUA3WeaponFXComponent>("WeaponFXComponent");
}

void AUA3Projectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &AUA3Projectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void AUA3Projectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld())
        return;

    MovementComponent->StopMovementImmediately();
    // make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(), //
        DamageAmount,                               //
        GetActorLocation(),                         //
        DamageRadius,                               //
        UDamageType::StaticClass(),                 //
        {nullptr},
        // {GetOwner()},                               //
        this,            //
        GetController(), //
        DoFullDamage);

    //  DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 12, FColor::Red, false, 5.0f);
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* AUA3Projectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}