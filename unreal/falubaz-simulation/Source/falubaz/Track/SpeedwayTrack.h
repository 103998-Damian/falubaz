#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "SpeedwayTrack.generated.h"

/**
 * Tor żużlowy – proceduralny owal na podstawie Spline.
 * Wymiary: Zielona Góra ~344m obwodu, szerokość 12m.
 */
UCLASS()
class FALUBAZ_API ASpeedwayTrack : public AActor
{
    GENERATED_BODY()

public:
    ASpeedwayTrack();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USplineComponent* TrackSpline;

    /** Mesh użyty do renderowania nawierzchni toru */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Config")
    UStaticMesh* TrackMesh;

    /** Długość każdej prostej [cm] */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Config")
    float StraightLength = 8000.f;

    /** Promień łuku [cm] – Zielona Góra ~3000cm */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Config")
    float TurnRadius = 3000.f;

    /** Szerokość toru [cm] */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Config")
    float TrackWidth = 1200.f;

    /** Liczba segmentów na każdy łuk */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Config")
    int32 TurnSegments = 16;

private:
    void GenerateOvalSpline();
    void BuildSplineMeshes();

    UPROPERTY()
    TArray<USplineMeshComponent*> SplineMeshes;
};
