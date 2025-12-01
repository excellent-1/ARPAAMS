   #include "IBeamformingStrategy.h"
   class MonopulseStrategy : public IBeamformingStrategy {
   public:
       void applyBeamforming(AntennaArray& array, const TargetInfo& target) override {
           // Monopulse beamforming logic
       }
   };
