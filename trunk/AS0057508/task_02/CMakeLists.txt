cmake_minimum_required(VERSION 3.14)
project(Lab2_Testing CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(program src/main.cpp src/model.cpp src/model.h)

add_executable(unit_tests test/unit_tests.cpp src/model.cpp src/model.h)
target_link_libraries(unit_tests gtest_main)

include(CTest)
enable_testing()
add_test(NAME RunAllProjectTests COMMAND unit_tests)
