cmake_minimum_required(VERSION 3.10)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(temperature_model main.cpp)

target_include_directories(temperature_model PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

