#pragma once
#include "IFaultObserver.h"
#include "FaultEvent.h"
#include <vector>
#include <mutex>

class RFPayloadMonitor {
    std::vector<IFaultObserver*> observers;
    mutable std::mutex mtx;
public:
    // Register an observer (thread-safe)
    void registerObserver(IFaultObserver* observer);

    // Unregister an observer
    void unregisterObserver(IFaultObserver* observer);

    // Detect a fault and notify observers (snapshot semantics)
    void detectFault(const FaultEvent& event);
};
