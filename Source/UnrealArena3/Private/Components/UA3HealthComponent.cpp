// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Components/UA3HealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "UA3_GameModeBase.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UUA3HealthComponent::UUA3HealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUA3HealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);
    SetArmor(DebugArmor);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UUA3HealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &UUA3HealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UUA3HealthComponent::OnTakeRadialDamage);
    }
}

void UUA3HealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UUA3HealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UUA3HealthComponent::SetArmor(float NewArmor)
{
    const auto NextArmor = FMath::Clamp(NewArmor, 0.0f, MaxArmor);
    const auto ArmorDelta = NextArmor - Armor;

    Armor = NextArmor;
    OnArmorChanged.Broadcast(Armor, ArmorDelta);
}

void UUA3HealthComponent::PlayCameraShake()
{
    if (IsDead())
        return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

bool UUA3HealthComponent::TryToHeal(float HealAmount)
{
    if (IsDead() || IsHealthFull())
        return false;

    SetHealth(Health + HealAmount);
    return true;
}

bool UUA3HealthComponent::TryToAddArmor(float ArmorAmount)
{
    if (IsDead() || IsArmorFull())
        return false;

    SetArmor(Armor + ArmorAmount);
    return true;
}

bool UUA3HealthComponent::IsArmorFull() const
{
    return FMath::IsNearlyEqual(Armor, MaxArmor);
}

bool UUA3HealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UUA3HealthComponent::SetIsScoresCalled(int32 Value)
{
    ScoresValue = Value;
}

void UUA3HealthComponent::Killed(AController* KillerController)
{

    const auto GameMode = Cast<AUA3_GameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}

void UUA3HealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
    UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    ApplyDamage(FinalDamage, InstigatedBy);
}

void UUA3HealthComponent::OnTakeRadialDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);
}

void UUA3HealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
}

void UUA3HealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    else if (Armor != 0.0f || IsDead())
    {
        const auto ArmorModifier = Damage * 0.65;
        const auto HealthModifier = Damage * 0.35;
        SetHealth(Health - HealthModifier);
        SetArmor(Armor - ArmorModifier);

        UE_LOG(LogHealthComponent, Display, TEXT("Amor test"));

        PlayCameraShake();
        ReportDamageEvent(Damage, InstigatedBy);
    }
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UUA3HealthComponent::HealUpdate, HealUpdateTime, true, HealDelayTime);
    }

    PlayCameraShake();
    ReportDamageEvent(Damage, InstigatedBy);
}

float UUA3HealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character ||            //
        !Character->GetMesh() || //
        !Character->GetMesh()->GetBodyInstance(BoneName))
        return 1.0f;

    const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial))
        return 1.0f;

    return DamageModifiers[PhysMaterial];
}

void UUA3HealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
    if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
        return;
    UAISense_Damage::ReportDamageEvent(
        GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage, InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}
