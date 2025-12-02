#pragma once
#include "FaultEvent.h"

class IFaultObserver {
public:
    virtual void notifyFault(const FaultEvent& event) = 0;
    virtual ~IFaultObserver() = default;
};
