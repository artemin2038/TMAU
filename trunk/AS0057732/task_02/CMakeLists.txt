cmake_minimum_required(VERSION 3.14)
project(task02_testing CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(src)

add_executable(task02_app
    src/main.cpp
    src/simulation.cpp
)

add_executable(task02_tests
    test/test_core.cpp
    src/simulation.cpp
)

target_link_libraries(task02_tests gtest gtest_main)

enable_testing()
add_test(NAME CoreTests COMMAND task02_tests)
