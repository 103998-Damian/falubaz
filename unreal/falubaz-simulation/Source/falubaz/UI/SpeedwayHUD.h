#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpeedwayHUD.generated.h"

class UTextBlock;

/**
 * HUD motocykla – wyświetla prędkość i obroty silnika.
 */
UCLASS()
class FALUBAZ_API USpeedwayHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    /** Aktualizuje wyświetlane wartości */
    UFUNCTION(BlueprintCallable)
    void UpdateHUD(float SpeedKMH, float RPM);

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SpeedText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* RPMText;
};
