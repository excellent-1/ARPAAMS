#ifndef BEAMFORMINGENGINECONTEXT_H
#define BEAMFORMINGENGINECONTEXT_H

#include <memory>
#include "IBeamformingStrategy.h"
#include "AntennaArray.h"
#include "TargetInfo.h"
#include "IBeamformingStrategy.h"

class BeamformingEngineContext {
    std::unique_ptr<IBeamformingStrategy> strategy;
public:
    void setStrategy(std::unique_ptr<IBeamformingStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    void process(AntennaArray& array, const TargetInfo& target) {
        if (strategy) {
            strategy->applyBeamforming(array, target);
        }
    }
};
