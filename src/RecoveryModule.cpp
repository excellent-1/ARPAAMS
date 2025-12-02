#include "RecoveryModule.h"
#include <iostream>

RecoveryModule::RecoveryModule() : recoveryTriggered(false) {}

void RecoveryModule::notifyFault(const FaultEvent& event) {
    lastEventTime = std::chrono::steady_clock::now();
    recoveryTriggered.store(true);
    std::cerr << "[RecoveryModule] Recovery triggered for source: " << event.source
              << " code: " << event.code << "\n";
}

bool RecoveryModule::wasRecoveryTriggered() const { return recoveryTriggered.load(); }
std::chrono::steady_clock::time_point RecoveryModule::getLastEventTime() const { return lastEventTime; }
void RecoveryModule::clear() { recoveryTriggered.store(false); }
