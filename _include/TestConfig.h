#pragma once
#include <atomic>

extern std::atomic<bool> HardFailOrWarning;

bool getStrictTimingFromEnv();
