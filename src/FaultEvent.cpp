#include "FaultEvent.h"

FaultEvent::FaultEvent(const std::string& src, int c, Severity s)
    : source(src), code(c), severity(s), timestamp(std::chrono::steady_clock::now()) {}
