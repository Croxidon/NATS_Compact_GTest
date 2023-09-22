cmake_minimum_required(VERSION 3.16)
project(NATS_Compact_GTest VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS thread chrono)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/8a6feabf04bec8fb125e0df0ad1195c42350725f.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(
  NATS_Compact_GTest
  NATS_Compact_GTest.cpp
)
add_subdirectory(NATS_Compact_Test)

target_link_libraries(NATS_Compact_GTest PUBLIC NATS_Compact_Test GTest::gtest_main Boost::thread Boost::chrono)
target_include_directories(NATS_Compact_GTest PUBLIC
                           "${PROJECT_BINARY_DIR}"
                             "${PROJECT_SOURCE_DIR}/NATS_Compact_Test"
                             "/usr/local/include/nats"
                             "/usr/local/include/gtest"
                           )
target_link_libraries(NATS_Compact_GTest PUBLIC "/usr/local/lib/libnats.so")
include(GoogleTest)
gtest_discover_tests(NATS_Compact_GTest)
