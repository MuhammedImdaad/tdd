cmake_minimum_required(VERSION 3.28)
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

# Add a single file where tests and code are together
add_executable(unitTest src/main.cpp)

target_include_directories(unitTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(unitTest gtest gtest_main)

# Discover and run tests
include(GoogleTest)
gtest_discover_tests(unitTest)
