#pragma once
#include <cmath>

/**
 * @brief Represents information about a detected radar target.
 *        Beamforming strategies use this as input.
 */
class TargetInfo
{
public:
    TargetInfo() = default;

    TargetInfo(double azimuthDeg, double elevationDeg, double rangeMeters)
        : azimuth(azimuthDeg), elevation(elevationDeg), range(rangeMeters) {}

    double getAzimuth() const { return azimuth; }
    double getElevation() const { return elevation; }
    double getRange() const { return range; }

private:
    double azimuth{0.0};     // Degrees
    double elevation{0.0};   // Degrees
    double range{0.0};       // Meters
};
