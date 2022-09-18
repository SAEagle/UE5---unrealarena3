// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UI/UA3PlayerHUDWidget.h"
#include "Components/UA3HealthComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "UA3Utils.h"
#include "Components/ProgressBar.h"
#include "Player/UA3PlayerState.h"

float UUA3PlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)
        return 0.0f;

    return HealthComponent->GetHealthPercent();
}

float UUA3PlayerHUDWidget::GetHealth() const
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)
        return 0.0f;

    return HealthComponent->GetHealth();
}

float UUA3PlayerHUDWidget::GetArmor() const
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)
        return 0.0f;

    return HealthComponent->GetArmor();
}

bool UUA3PlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UUA3PlayerHUDWidget::GetWeaponUIData(int32 Index, FWeaponUIData& UIData) const
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetWeaponUIData(Index, UIData);
}

bool UUA3PlayerHUDWidget::GetWeaponUIVisibility(int32 Index, bool Value) const
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetWeaponUIVisibility(Index, Value);
}

bool UUA3PlayerHUDWidget::GetWeaponAmmoData(int32 Index, FAmmoData& AmmoData) const
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetWeaponAmmoData(Index, AmmoData);
}

bool UUA3PlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UUA3PlayerHUDWidget::GetCurrentWeaponIndex(int32 Index) const
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponIndex(Index);
}

bool UUA3PlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool UUA3PlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 UUA3PlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller)
        return 0;

    const auto PlayerState = Cast<AUA3PlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString UUA3PlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }

    return BulletStr;
}

void UUA3PlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UUA3PlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void UUA3PlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

void UUA3PlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UUA3PlayerHUDWidget::OnHealthChanged);
    }

    UpdateHealthBar();
}

void UUA3PlayerHUDWidget::UpdateHealthBar()
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}

int32 UUA3PlayerHUDWidget::IsScoresCalled() const
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)
        return 0;
    return HealthComponent->GetScoresValue();
}
