#ifndef IBEAMFORMINGSTRATEGY_H
#define IBEAMFORMINGSTRATEGY_H
    // Forward declarations or actual definitions for AntennaArray and TargetInfo
    class AntennaArray;
    class TargetInfo;

    class IBeamformingStrategy 
    {
    public:
        virtual void applyBeamforming(AntennaArray& array, const TargetInfo& target) = 0;
        virtual ~IBeamformingStrategy() = default;
    };
#endif // IBEAMFORMINGSTRATEGY_H