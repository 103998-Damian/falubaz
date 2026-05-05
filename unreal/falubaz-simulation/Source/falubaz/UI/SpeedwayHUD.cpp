#include "SpeedwayHUD.h"
#include "Components/TextBlock.h"

void USpeedwayHUD::UpdateHUD(float SpeedKMH, float RPM)
{
    if (SpeedText)
    {
        SpeedText->SetText(FText::FromString(
            FString::Printf(TEXT("Speed: %.1f km/h"), SpeedKMH)));
    }

    if (RPMText)
    {
        RPMText->SetText(FText::FromString(
            FString::Printf(TEXT("RPM: %.0f"), RPM)));
    }
}
