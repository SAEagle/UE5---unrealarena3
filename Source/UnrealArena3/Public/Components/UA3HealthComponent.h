// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UA3CoreTypes.h"
#include "UA3HealthComponent.generated.h"

class UCameraShake;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARENA3_API UUA3HealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUA3HealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category = "Armor")
    float GetArmor() const { return Armor; }

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;
    FOnArmorChangedSignature OnArmorChanged;

    UFUNCTION(BlueprintCallable)
    bool TryToHeal(float HealAmount);
    bool TryToAddArmor(float ArmorAmount);
    bool IsArmorFull() const;
    bool IsHealthFull() const;

    void SetIsScoresCalled(int32 ScoresValue);
    float GetScoresValue() const { return ScoresValue; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
    float HealDelayTime = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
    float HealModifier = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxArmor = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float DebugArmor = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    TMap<UPhysicalMaterial*, float> DamageModifiers;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;
    float Armor = 0.0f;
    int32 ScoresValue = 0;

    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent,
        FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo,
        class AController* InstigatedBy, AActor* DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);
    void SetArmor(float NewArmor);
    void PlayCameraShake();

    void Killed(AController* KillerController);
    void ApplyDamage(float Damage, AController* InstigatedBy);
    float GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName);

    void ReportDamageEvent(float Damage, AController* InstigatedBy);
};
