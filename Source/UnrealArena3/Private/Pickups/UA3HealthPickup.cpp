// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Pickups/UA3HealthPickup.h"
#include "Components/UA3HealthComponent.h"
#include "UA3Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AUA3HealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = UA3Utils::GetUA3PlayerComponent<UUA3HealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;
    else if (HealthComponent && IsItArmor == 0)
        return HealthComponent->TryToHeal(HealthAmount);

    // UE_LOG(LogHealthPickup, Display, TEXT("Player was healed!"));
    else
        return HealthComponent->TryToAddArmor(ArmorAmount);
}
