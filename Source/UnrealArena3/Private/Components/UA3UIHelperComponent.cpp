// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Components/UA3UIHelperComponent.h"

UUA3UIHelperComponent::UUA3UIHelperComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUA3UIHelperComponent::SetPickUIData(FPickupUIData PickupData)
{
    PickupUIData = PickupData;
    SetPickupAdded(true);
}

void UUA3UIHelperComponent::SetPickupAdded(bool value)
{
    IsPickupAdded = value;
}

bool UUA3UIHelperComponent::GetPickupUIData(FPickupUIData& PickupData) const
{
    PickupData = PickupUIData;
    return true;
}
