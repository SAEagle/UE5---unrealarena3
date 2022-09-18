#pragma once
#include "UA3CoreTypes.generated.h"
// weapon
class AUA3BaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, AUA3BaseWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AUA3BaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArmorChangedSignature, float, float);

// VFX
class UNiagaraSystem;
class USoundCue;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInterface* Material;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.8f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    USoundCue* Sound;
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 PlayersNum = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 RoundsNum = 4;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 RoundTime = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FLinearColor DefaultTeamColor = FLinearColor::Red;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 RespawnTime = 15;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 RoundKillTarget = 0;
};

UENUM(BlueprintType)
enum class EUA3MatchState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    GameOver,
    Scores,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EUA3MatchState);

USTRUCT(BlueprintType)
struct FLevelData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelDisplayName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    UTexture2D* LevelThumb;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);
