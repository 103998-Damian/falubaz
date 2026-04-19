#include "SpeedwayMovementComponent.h"
#include "Math/UnrealMathUtility.h"

USpeedwayMovementComponent::USpeedwayMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // Żużel: jeden bieg, brak skrzyni
    TransmissionSetup.bUseAutomaticGears = true;
    TransmissionSetup.ForwardGearRatios.SetNum(1);
    TransmissionSetup.ForwardGearRatios[0] = 3.5f;
    TransmissionSetup.ReverseGearRatios.Empty(); // brak biegu wstecznego

    // Silnik żużlowy: wysoki moment, wysokie obroty
    EngineSetup.MaxRPM = 9000.f;
    EngineSetup.MaxTorque = 300.f;
}

void USpeedwayMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    ApplySpeedwayFriction();
}

void USpeedwayMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UpdateDriftAngle();
}

void USpeedwayMovementComponent::ApplySpeedwayFriction()
{
    // Koło 0 = przednie, Koło 1 = tylne (standardowy układ 2-kołowy)
    if (WheelSetups.Num() >= 2)
    {
        // Tarcie boczne ustawiane przez wheel setup w Blueprint
        // Tutaj możemy nadpisać w runtime jeśli potrzeba
    }
}

void USpeedwayMovementComponent::UpdateDriftAngle()
{
    const FVector LocalVelocity = GetOwner()->GetActorTransform().InverseTransformVector(GetOwner()->GetVelocity());
    if (LocalVelocity.Size() > 10.f)
    {
        DriftAngle = FMath::RadiansToDegrees(FMath::Atan2(LocalVelocity.Y, LocalVelocity.X));
    }
    else
    {
        DriftAngle = 0.f;
    }
}
