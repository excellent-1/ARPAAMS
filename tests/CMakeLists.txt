find_package(GTest REQUIRED)
enable_testing()

add_executable(patterns_tests
    test_main.cpp
    patterns_tests.cpp
)

target_include_directories(patterns_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(patterns_tests PRIVATE arpaams GTest::gtest GTest::gtest_main pthread)

add_test(NAME patterns_tests COMMAND patterns_tests)


option(TEST_JUNIT "Enable JUnit XML output" OFF)
if(TEST_JUNIT)
    add_test(NAME arpaams_tests COMMAND arpaams_tests --gtest_output=xml:test-results/junit.xml)
endif()

#enable_testing()

#add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)

#add_executable(beamforming_tests test_beamforming.cpp)
#target_link_libraries(beamforming_tests gtest gtest_main ARPAAMS)

#add_test(NAME beamforming_tests COMMAND beamforming_tests)
