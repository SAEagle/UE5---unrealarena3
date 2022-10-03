// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Pickups/UA3AmmoPickup.h"
#include "Components/UA3HealthComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "Components/UA3UIHelperComponent.h"
#include "UA3Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AUA3AmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto WeaponComponent = UA3Utils::GetUA3PlayerComponent<UUA3WeaponComponent>(PlayerPawn);
    const auto UIHelper = UA3Utils::GetUA3PlayerComponent<UUA3UIHelperComponent>(PlayerPawn);
    if (!WeaponComponent || !UIHelper)
        return false;
    else
        //  UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
        UIHelper->SetPickUIData(PickupUIData);
        return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
   
}
