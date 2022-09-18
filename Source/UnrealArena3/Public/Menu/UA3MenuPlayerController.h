// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UA3MenuPlayerController.generated.h"

UCLASS()
class UNREALARENA3_API AUA3MenuPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
