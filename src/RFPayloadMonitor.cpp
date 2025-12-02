#include "RFPayloadMonitor.h"
#include <algorithm>

void RFPayloadMonitor::registerObserver(IFaultObserver* observer) {
    std::lock_guard<std::mutex> lk(mtx);
    observers.push_back(observer);
}

void RFPayloadMonitor::unregisterObserver(IFaultObserver* observer) {
    std::lock_guard<std::mutex> lk(mtx);
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void RFPayloadMonitor::detectFault(const FaultEvent& event) {
    std::vector<IFaultObserver*> snapshot;
    {
        std::lock_guard<std::mutex> lk(mtx);
        snapshot = observers;
    }
    for (auto obs : snapshot) {
        if (obs) obs->notifyFault(event);
    }
}
