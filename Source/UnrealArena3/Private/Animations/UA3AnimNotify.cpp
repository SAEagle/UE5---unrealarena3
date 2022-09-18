// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development


#include "Animations/UA3AnimNotify.h"


void UUA3AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
