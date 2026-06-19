cmake_minimum_required(VERSION 3.14)
project(Task2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(temperature_model STATIC
    srctemperature_model.cpp
)

# Основная программа
add_executable(task2 srcmain.cpp)
target_link_libraries(task2 temperature_model)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL httpsgithub.comgooglegoogletestarchiverefstagsv1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Тесты
enable_testing()

add_executable(tests testtest_temperature.cpp)
target_link_libraries(tests temperature_model gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)