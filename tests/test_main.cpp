#include <gtest/gtest.h>
#include "TestConfig.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    HardFailOrWarning.store(getStrictTimingFromEnv());
    return RUN_ALL_TESTS();
}
