cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "/home/user/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(tdd)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch and add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package(nlohmann_json CONFIG REQUIRED)

file (GLOB sources src/*.cpp)
file (GLOB testSources tests/*.cpp)

add_executable(allTests ${testSources} ${sources})
target_include_directories(allTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(allTests GTest::gtest_main GTest::gmock_main nlohmann_json::nlohmann_json)

# cmake -DSPECIFIC_TEST=<testFile>.cpp ..
# make currentTest
set(SPECIFIC_TEST "" CACHE STRING "Specific test file to build")
if (DEFINED SPECIFIC_TEST AND NOT "${SPECIFIC_TEST}" STREQUAL "")
    message(STATUS "Building specific test: ${SPECIFIC_TEST}")
    add_executable(currentTest tests/${SPECIFIC_TEST} ${sources})
    target_include_directories(currentTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(currentTest GTest::gtest_main GTest::gmock_main nlohmann_json::nlohmann_json)  
endif()

# Discover and run tests
include(GoogleTest)
gtest_discover_tests(allTests)
