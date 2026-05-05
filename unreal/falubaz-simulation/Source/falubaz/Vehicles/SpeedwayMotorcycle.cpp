#include "SpeedwayMotorcycle.h"
#include "../UI/SpeedwayHUD.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ASpeedwayMotorcycle::ASpeedwayMotorcycle()
{
    PrimaryActorTick.bCanEverTick = true;

    // Kapsuła jako root – ma kolizję i fizykę od razu
    PhysicsBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PhysicsBody"));
    PhysicsBody->SetCapsuleSize(40.f, 60.f); // promień 40cm, wysokość 120cm
    PhysicsBody->SetSimulatePhysics(true);
    PhysicsBody->SetCollisionProfileName(TEXT("PhysicsActor"));
    SetRootComponent(PhysicsBody);

    // Mesh wizualny – przypisz w Blueprint
    MotorcycleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotorcycleMesh"));
    MotorcycleMesh->SetupAttachment(RootComponent);
    MotorcycleMesh->SetSimulatePhysics(false);
    MotorcycleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Kamera
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 500.f;
    SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
    SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
    SpringArm->bUsePawnControlRotation = false;
    SpringArm->bInheritYaw = true;
    SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ASpeedwayMotorcycle::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }

        // Utwórz HUD
        if (HUDClass)
        {
            HUDWidget = Cast<USpeedwayHUD>(CreateWidget<UUserWidget>(PC, HUDClass));
            if (HUDWidget)
            {
                HUDWidget->AddToViewport();
            }
        }
    }
}

void ASpeedwayMotorcycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Siła napędowa
    const FVector ForwardForce = GetActorForwardVector() * ThrottleInput * EngineForce;
    PhysicsBody->AddForce(ForwardForce, NAME_None, true);

    // Skręt
    const FVector TorqueVec = FVector(0.f, 0.f, SteerInput * SteerTorque);
    PhysicsBody->AddTorqueInDegrees(TorqueVec, NAME_None, true);

    // Opór powietrza
    const FVector Velocity = PhysicsBody->GetPhysicsLinearVelocity();
    PhysicsBody->AddForce(-Velocity * DragCoefficient, NAME_None, false);

    // Aktualizuj HUD
    if (HUDWidget)
    {
        const float SpeedCMS = Velocity.Size();
        const float SpeedKMH = SpeedCMS * 0.036f;
        // Obroty żużlowe: 4000 RPM na starcie, 9000 RPM przy 120 km/h
        // Silnik zawsze na wysokich obrotach – brak skrzyni biegów
        const float BaseRPM = ThrottleInput > 0.f ? 4000.f : 0.f;
        const float RPM = FMath::Lerp(BaseRPM, 9000.f, FMath::Clamp(SpeedKMH / 120.f, 0.f, 1.f));
        HUDWidget->UpdateHUD(SpeedKMH, RPM);
    }
}

void ASpeedwayMotorcycle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ASpeedwayMotorcycle::HandleThrottle);
        EIC->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ASpeedwayMotorcycle::HandleThrottle);
        EIC->BindAction(SteerAction, ETriggerEvent::Triggered, this, &ASpeedwayMotorcycle::HandleSteer);
        EIC->BindAction(SteerAction, ETriggerEvent::Completed, this, &ASpeedwayMotorcycle::HandleSteer);
    }
}

void ASpeedwayMotorcycle::HandleThrottle(const FInputActionValue& Value)
{
    ThrottleInput = Value.Get<float>();
}

void ASpeedwayMotorcycle::HandleSteer(const FInputActionValue& Value)
{
    SteerInput = Value.Get<float>();
}
