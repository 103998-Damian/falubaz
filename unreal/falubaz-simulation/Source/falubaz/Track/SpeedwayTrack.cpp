#include "SpeedwayTrack.h"
#include "Math/UnrealMathUtility.h"

ASpeedwayTrack::ASpeedwayTrack()
{
    PrimaryActorTick.bCanEverTick = false;

    TrackSpline = CreateDefaultSubobject<USplineComponent>(TEXT("TrackSpline"));
    SetRootComponent(TrackSpline);
}

void ASpeedwayTrack::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    GenerateOvalSpline();
    BuildSplineMeshes();
}

void ASpeedwayTrack::BeginPlay()
{
    Super::BeginPlay();
}

void ASpeedwayTrack::GenerateOvalSpline()
{
    TrackSpline->ClearSplinePoints();

    const float HalfStraight = StraightLength * 0.5f;

    // Prosta dolna: lewa -> prawa
    TrackSpline->AddSplinePoint(FVector(-HalfStraight, -TurnRadius, 0.f), ESplineCoordinateSpace::Local);
    TrackSpline->AddSplinePoint(FVector( HalfStraight, -TurnRadius, 0.f), ESplineCoordinateSpace::Local);

    // Prawy łuk (półkole)
    for (int32 i = 1; i <= TurnSegments; i++)
    {
        const float Angle = FMath::DegreesToRadians(-90.f + 180.f * i / TurnSegments);
        const float X = HalfStraight + TurnRadius * FMath::Cos(Angle);
        const float Y = TurnRadius * FMath::Sin(Angle);
        TrackSpline->AddSplinePoint(FVector(X, Y, 0.f), ESplineCoordinateSpace::Local);
    }

    // Prosta górna: prawa -> lewa
    TrackSpline->AddSplinePoint(FVector(-HalfStraight, TurnRadius, 0.f), ESplineCoordinateSpace::Local);

    // Lewy łuk (półkole)
    for (int32 i = 1; i <= TurnSegments; i++)
    {
        const float Angle = FMath::DegreesToRadians(90.f + 180.f * i / TurnSegments);
        const float X = -HalfStraight + TurnRadius * FMath::Cos(Angle);
        const float Y = TurnRadius * FMath::Sin(Angle);
        TrackSpline->AddSplinePoint(FVector(X, Y, 0.f), ESplineCoordinateSpace::Local);
    }

    TrackSpline->SetClosedLoop(true);
    TrackSpline->UpdateSpline();
}

void ASpeedwayTrack::BuildSplineMeshes()
{
    // Usuń stare segmenty
    for (USplineMeshComponent* Mesh : SplineMeshes)
    {
        if (Mesh) Mesh->DestroyComponent();
    }
    SplineMeshes.Empty();

    if (!TrackMesh) return;

    const int32 NumPoints = TrackSpline->GetNumberOfSplinePoints();
    for (int32 i = 0; i < NumPoints; i++)
    {
        const int32 NextIndex = (i + 1) % NumPoints;

        USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
        SplineMesh->SetStaticMesh(TrackMesh);
        SplineMesh->SetMobility(EComponentMobility::Static);
        SplineMesh->SetupAttachment(RootComponent);
        SplineMesh->RegisterComponent();

        FVector StartPos, StartTan, EndPos, EndTan;
        TrackSpline->GetLocationAndTangentAtSplinePoint(i,       StartPos, StartTan, ESplineCoordinateSpace::Local);
        TrackSpline->GetLocationAndTangentAtSplinePoint(NextIndex, EndPos, EndTan, ESplineCoordinateSpace::Local);

        SplineMesh->SetStartAndEnd(StartPos, StartTan, EndPos, EndTan);
        SplineMesh->SetStartScale(FVector2D(TrackWidth / 100.f, 1.f));
        SplineMesh->SetEndScale(FVector2D(TrackWidth / 100.f, 1.f));

        SplineMeshes.Add(SplineMesh);
    }
}
