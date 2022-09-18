// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Pickups/UA3BasePickup.h"
#include "UA3WeaponPickup.generated.h"

UCLASS()
class UNREALARENA3_API AUA3WeaponPickup : public AUA3BasePickup
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<AUA3BaseWeapon> WeaponTypeToAdd;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    int32 AmmoAmountWithNewWeapon = 10;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
