cmake_minimum_required(VERSION 3.14)
project(Lab1_Task02 CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматически скачиваем и подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Форсируем использование правильных настроек компилятора для gtest на Windows/MSVC
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Указываем, где искать заголовочные файлы (чтобы тесты видели simulation.h)
include_directories(src)

# Главное приложение (файлы лежат в папке src)
add_executable(main_app 
    src/main.cpp 
    src/simulation.cpp
)

# Модульные тесты (тестовый файл из папки test + логика из папки src)
add_executable(unit_tests 
    test/test_simulation.cpp 
    src/simulation.cpp
)

# Линкуем тесты с библиотеками Google Test
target_link_libraries(unit_tests gtest gtest_main)

# Включаем поддержку тестов в CMake
enable_testing()
add_test(NAME CoreSimulationTests COMMAND unit_tests)