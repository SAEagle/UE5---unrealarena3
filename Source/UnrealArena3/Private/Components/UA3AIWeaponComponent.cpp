// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Components/UA3AIWeaponComponent.h"
#include "Weapon/UA3BaseWeapon.h"

void UUA3AIWeaponComponent::StartFire()
{
    if (!CanFire())
        return;

    if (CurrentWeapon->IsClipEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UUA3AIWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextIndex]->IsClipEmpty())
            break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
