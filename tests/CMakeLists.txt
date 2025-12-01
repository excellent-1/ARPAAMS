enable_testing()

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)

add_executable(beamforming_tests test_beamforming.cpp)
target_link_libraries(beamforming_tests gtest gtest_main ARPAAMS)

add_test(NAME beamforming_tests COMMAND beamforming_tests)
