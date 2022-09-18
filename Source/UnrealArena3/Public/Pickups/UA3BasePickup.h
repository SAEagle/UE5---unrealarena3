// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UA3BasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class UNREALARENA3_API AUA3BasePickup : public AActor
{
    GENERATED_BODY()

public:
    AUA3BasePickup();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
    bool OneTimeSpawner = false;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* PickTakenSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
    float RotationYaw = 0.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    FTimerHandle RespawnTimerHandle;

    virtual bool GivePickupTo(APawn* PlayerPawn);

    void PickUpWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
