#pragma once
#include "IFaultObserver.h"
#include "FaultEvent.h"
#include <atomic>
#include <chrono>

class RecoveryModule : public IFaultObserver {
    std::atomic<bool> recoveryTriggered;
    std::chrono::steady_clock::time_point lastEventTime;
public:
    RecoveryModule();
    void notifyFault(const FaultEvent& event) override;
    bool wasRecoveryTriggered() const;
    std::chrono::steady_clock::time_point getLastEventTime() const;
    void clear();
};
