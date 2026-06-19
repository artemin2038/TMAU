cmake_minimum_required(VERSION 3.15)
project(task_02_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Используем Git для загрузки стабильной версии GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

# Настройка для Windows (MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Создаем исполняемый файл
add_executable(run_tests 
    src/model.cpp 
    test/test_model.cpp
)

# Подключаем библиотеку
target_link_libraries(run_tests GTest::gtest_main)