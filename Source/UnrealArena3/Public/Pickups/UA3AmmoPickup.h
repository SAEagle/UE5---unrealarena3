// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Pickups/UA3BasePickup.h"
#include "UA3AmmoPickup.generated.h"

class AUA3BaseWeapon;

UCLASS()
class UNREALARENA3_API AUA3AmmoPickup : public AUA3BasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<AUA3BaseWeapon> WeaponType;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
