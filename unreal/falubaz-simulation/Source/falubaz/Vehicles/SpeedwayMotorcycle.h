#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "SpeedwayMotorcycle.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class USpeedwayHUD;

UCLASS()
class FALUBAZ_API ASpeedwayMotorcycle : public APawn
{
    GENERATED_BODY()

public:
    ASpeedwayMotorcycle();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
    virtual void Tick(float DeltaTime) override;

    // --- Komponenty ---

    /** Kapsuła fizyczna – root z kolizją i fizyką */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* PhysicsBody;

    /** Mesh wizualny motocykla – przypisz w Blueprint */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MotorcycleMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* Camera;

    // --- Input ---

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* ThrottleAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* SteerAction;

    // --- Parametry fizyki ---

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float EngineForce = 5000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float SteerTorque = 3000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float DragCoefficient = 0.5f;

    // --- Stan ---

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float ThrottleInput = 0.f;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float SteerInput = 0.f;

    // --- HUD ---

    /** Klasa widgetu HUD – przypisz WBP_HUD w Blueprint */
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> HUDClass;

private:
    void HandleThrottle(const FInputActionValue& Value);
    void HandleSteer(const FInputActionValue& Value);

    UPROPERTY()
    USpeedwayHUD* HUDWidget = nullptr;
};
