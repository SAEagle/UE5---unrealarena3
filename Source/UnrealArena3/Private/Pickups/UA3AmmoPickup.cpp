// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Pickups/UA3AmmoPickup.h"
#include "Components/UA3HealthComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "UA3Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AUA3AmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;
    else
        return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
    //  UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
}
