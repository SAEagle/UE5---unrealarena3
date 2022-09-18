// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Pickups/UA3WeaponPickup.h"
#include "Components/UA3HealthComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "UA3Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponPickup, All, All);

bool AUA3WeaponPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;
    UE_LOG(LogAmmoPickup, Display, TEXT("Weapon was taken"));
    return WeaponComponent->TryToAddAmmoFirstTime(WeaponTypeToAdd, AmmoAmountWithNewWeapon);
}