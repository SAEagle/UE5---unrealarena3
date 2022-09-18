// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/UA3CharacterAI.h"
#include "AI/UA3AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/UA3AIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/UA3HealthBarWidget.h"
#include "Components/UA3HealthComponent.h"

AUA3CharacterAI::AUA3CharacterAI(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UUA3AIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AUA3AIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AUA3CharacterAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateHealthWidgetVisibility();
}

void AUA3CharacterAI::BeginPlay()
{
    Super::BeginPlay();
}

void AUA3CharacterAI::OnDeath()
{
    Super::OnDeath();

    SetLifeSpan(LifeSpanOnDeath);

    const auto UA3Controller = Cast<AAIController>(Controller);
    if (UA3Controller && UA3Controller->BrainComponent)
    {
        UA3Controller->BrainComponent->Cleanup();
    }
}

void AUA3CharacterAI::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<UUA3HealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget)
        return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AUA3CharacterAI::UpdateHealthWidgetVisibility()
{
    if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;
    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
