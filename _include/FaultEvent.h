#pragma once
#include <string>
#include <chrono>

struct FaultEvent {
    enum class Severity { INFO, WARNING, CRITICAL };
    std::string source;
    int code;
    Severity severity;
    std::chrono::steady_clock::time_point timestamp;

    FaultEvent(const std::string& src = "",
               int c = 0,
               Severity s = Severity::INFO);
};
