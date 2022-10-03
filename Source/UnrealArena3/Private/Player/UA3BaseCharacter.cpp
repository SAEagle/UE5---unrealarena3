// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Player/UA3BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/UA3CharacterMovementComponent.h"
#include "Components/UA3HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "Components/UA3UIHelperComponent.h"
#include "Components/CapsuleComponent.h"
#include "UA3BaseCharacter.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

AUA3BaseCharacter::AUA3BaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UUA3HealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UUA3WeaponComponent>("WeaponComponent");
    UIHelperComponent = CreateDefaultSubobject<UUA3UIHelperComponent>("UIHelperComponent");
}

void AUA3BaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &AUA3BaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AUA3BaseCharacter::OnHealthChanged);
}

void AUA3BaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AUA3BaseCharacter::OnHealthChanged(float Health, float HealthDelta) {}

void AUA3BaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocity = -GetVelocity().Z;
    if (FallVelocity < LandedDamageVelocity.X)
        return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocity);
    TakeDamage(FinalDamage, FPointDamageEvent{}, nullptr, nullptr);

    // UE_LOG(BaseCharacterLog, Display, TEXT("Final damage is %f"), FinalDamage);
}

bool AUA3BaseCharacter::IsRunning() const
{
    return false;
}

float AUA3BaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AUA3BaseCharacter::SpawnWeapon()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Weapon Spawn"));
}

void AUA3BaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst)
        return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void AUA3BaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    // PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    WeaponComponent->OnDeathCall();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->DetachFromParent(true); // add physics to the limbs after death
    SpawnWeapon();
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AUA3BaseCharacter::TurnOff()
{
    WeaponComponent->StopFire();
    Super::TurnOff();
}

void AUA3BaseCharacter::Reset()
{
    WeaponComponent->StopFire();
    Super::Reset();
}
