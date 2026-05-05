#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "SpeedwayMovementComponent.generated.h"

/**
 * Komponent ruchu motocykla żużlowego.
 * Żużel = brak hamulca tylnego, brak biegów, silny poślizg tylnego koła.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FALUBAZ_API USpeedwayMovementComponent : public UChaosWheeledVehicleMovementComponent
{
    GENERATED_BODY()

public:
    USpeedwayMovementComponent();

    /** Współczynnik tarcia bocznego tylnego koła (niski = łatwy drift) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speedway|Physics")
    float RearLateralFriction = 0.35f;

    /** Współczynnik tarcia bocznego przedniego koła */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speedway|Physics")
    float FrontLateralFriction = 0.75f;

    /** Aktualny kąt driftu [stopnie] */
    UPROPERTY(BlueprintReadOnly, Category = "Speedway|State")
    float DriftAngle = 0.f;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void ApplySpeedwayFriction();
    void UpdateDriftAngle();
};
