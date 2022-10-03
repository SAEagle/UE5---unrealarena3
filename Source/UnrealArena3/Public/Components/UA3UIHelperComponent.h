// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UA3CoreTypes.h"
#include "UA3UIHelperComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARENA3_API UUA3UIHelperComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUA3UIHelperComponent();

    void SetPickUIData(FPickupUIData PickupData);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetPickupAdded(bool value);

    bool GetPickupUIData(FPickupUIData& PickupData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetPickupAdded() const { return IsPickupAdded; }

private:
    FPickupUIData PickupUIData;
    bool IsPickupAdded = false;
};
