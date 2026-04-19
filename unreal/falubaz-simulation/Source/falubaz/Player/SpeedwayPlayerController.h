#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpeedwayPlayerController.generated.h"

/**
 * Kontroler gracza dla symulacji żużlowej.
 */
UCLASS()
class FALUBAZ_API ASpeedwayPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASpeedwayPlayerController();

protected:
    virtual void BeginPlay() override;
};
