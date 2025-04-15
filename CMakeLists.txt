cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "/home/user/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(YourProjectName)

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

file (GLOB sources src/*.cpp)
set (testSources tests/test7.cpp)
add_executable(unitTest ${testSources} ${sources})

target_include_directories(unitTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(unitTest GTest::gtest_main GTest::gmock_main nlohmann_json::nlohmann_json)

# Discover and run tests
include(GoogleTest)
gtest_discover_tests(unitTest)
