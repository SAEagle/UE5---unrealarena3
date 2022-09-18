// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Pickups/UA3BasePickup.h"
#include "UA3HealthPickup.generated.h"

UCLASS()
class UNREALARENA3_API AUA3HealthPickup : public AUA3BasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float HealthAmount = 40.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float ArmorAmount = 40.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float IsItArmor = 0; // 0 : 1 switch between armor pickups

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
