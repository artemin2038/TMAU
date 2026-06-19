cmake_minimum_required(VERSION 3.10)

# Имя вашего проекта
project(Lab1)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем исполняемый файл "my_program" из исходника "main.cpp"
add_executable(my_program main.cpp)
