// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Sound/UA3SoundFuncLib.h"
#include "Sound/SoundClass.h"

void UUA3SoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (!SoundClass)
        return;

    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UUA3SoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if (!SoundClass)
        return;

    const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
