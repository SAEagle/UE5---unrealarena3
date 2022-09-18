// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "UA3GameInstance.h"
#include "Sound/UA3SoundFuncLib.h"

void UUA3GameInstance::ToggleVolume()
{
    UUA3SoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
