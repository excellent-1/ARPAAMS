cmake_minimum_required(VERSION 3.14)

project(ARPAAMS 
    VERSION 0.1.0
    DESCRIPTION "ARPAAMS Project"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)

# Define source and include directories
set(SOURCE_DIR src)
set(INCLUDE_DIR _include)

# Gather all .cpp files in src automatically
file(GLOB SOURCES
    ${SOURCE_DIR}/*.cpp
)

# Create executable
add_executable(ARPAAMS ${SOURCES})

# Add include directory
target_include_directories(ARPAAMS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
)

# Optional CTest and CPack
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
