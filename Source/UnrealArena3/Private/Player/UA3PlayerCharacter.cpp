// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "Player/UA3PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/UA3WeaponComponent.h"
#include "Components/UA3HealthComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/UA3PlayerState.h"

AUA3PlayerCharacter::AUA3PlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called to bind functionality to input
void AUA3PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);
    check(GetMesh());

    PlayerInputComponent->BindAxis("MoveForward", this, &AUA3PlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AUA3PlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AUA3PlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AUA3PlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUA3PlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AUA3PlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AUA3PlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UUA3WeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("PrevWeapon", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::PrevWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::Reload);
    PlayerInputComponent->BindAction("Scores", IE_Pressed, this, &AUA3PlayerCharacter::OnShowScores);
    PlayerInputComponent->BindAction("Scores", IE_Released, this, &AUA3PlayerCharacter::OnHideScores);
    PlayerInputComponent->BindAction("Weapon 1", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::EquipWeapon1);
    PlayerInputComponent->BindAction("Weapon 2", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::EquipWeapon2);
    PlayerInputComponent->BindAction("Weapon 3", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::EquipWeapon3);
    PlayerInputComponent->BindAction("Weapon 5", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::EquipWeapon5);
    PlayerInputComponent->BindAction("Weapon 8", IE_Pressed, WeaponComponent, &UUA3WeaponComponent::EquipWeapon8);
}

void AUA3PlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AUA3PlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AUA3PlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void AUA3PlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void AUA3PlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void AUA3PlayerCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void AUA3PlayerCharacter::CheckCameraOverlap()
{
    const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for (auto MeshChild : MeshChildren)
    {
        const auto MeshChilGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChilGeometry)
        {
            MeshChilGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

void AUA3PlayerCharacter::OnShowScores()
{
    HealthComponent->SetIsScoresCalled(1);
}

void AUA3PlayerCharacter::OnHideScores()
{
    HealthComponent->SetIsScoresCalled(0);
}

bool AUA3PlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void AUA3PlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void AUA3PlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AUA3PlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AUA3PlayerCharacter::OnCameraCollisionEndOverlap);
}
