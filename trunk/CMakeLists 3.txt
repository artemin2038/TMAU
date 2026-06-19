cmake_minimum_required(VERSION 3.10)
project(TemperatureModelTests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../src)

add_executable(test_temperature 
    test_temperature.cpp
    ../src/main.cpp
)

target_link_libraries(test_temperature 
    ${GTEST_LIBRARIES}
    pthread
)

# Флаги для покрытия кода
target_compile_options(test_temperature PRIVATE -fprofile-arcs -ftest-coverage)
target_link_libraries(test_temperature PRIVATE -fprofile-arcs -ftest-coverage)

