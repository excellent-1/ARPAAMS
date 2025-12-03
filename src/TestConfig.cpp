#include "TestConfig.h"
#include <cstdlib>
#include <string>

std::atomic<bool> HardFailOrWarning{true};

bool getStrictTimingFromEnv() {
    const char* v = std::getenv("ARPAAMS_STRICT_TIMING");
    if (!v) return true;
    return std::string(v) == "1";
}
