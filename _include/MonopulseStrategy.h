#ifndef MONOPULSESTRATEGY_H
#define MONOPULSESTRATEGY_H

    #include "AntennaArray.h"
    #include "TargetInfo.h"
    #include "IBeamformingStrategy.h"
    class MonopulseStrategy : public IBeamformingStrategy {
    public:
        void applyBeamforming(AntennaArray& array, const TargetInfo& target) override {
            // Monopulse beamforming logic
        }
    };
#endif // MONOPULSESTRATEGY_H