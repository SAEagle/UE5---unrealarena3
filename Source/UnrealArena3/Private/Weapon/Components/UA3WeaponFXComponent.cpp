// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Weapon/Components/UA3WeaponFXComponent.h"
#include "../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogFX, All, All);

UUA3WeaponFXComponent::UUA3WeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUA3WeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // niagara fx
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
        ImpactData.NiagaraEffect,                              //
        Hit.ImpactPoint,                                       //
        Hit.ImpactNormal.Rotation());

    // decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        ImpactData.DecalData.Material,                                       //
        ImpactData.DecalData.Size,                                           //
        Hit.ImpactPoint,                                                     //
        Hit.ImpactNormal.Rotation());
    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }

    // sound to play
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}
