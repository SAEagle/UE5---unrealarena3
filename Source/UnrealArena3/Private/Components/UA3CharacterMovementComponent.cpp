// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development


#include "Components/UA3CharacterMovementComponent.h"
#include "Player/UA3BaseCharacter.h"

float UUA3CharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AUA3BaseCharacter* Player = Cast<AUA3BaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}
