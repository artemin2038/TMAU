# Отчёт по лабораторной работе №2
**Выполнил:** Дунаев Артем, 
**Группа** АС-577  

## 1. Цель работы
Практическое освоение методологии разработки и автоматизированного модульного тестирования (Unit Testing) математических моделей автоматизированных систем. Основные задачи: настройка многокомпонентного проекта через CMake, интеграция фреймворка Google Test (gtest) и верификация расчетов.

## 2. Структура проекта
Проект организован в соответствии с современными стандартами разработки на языке C++:

| Путь к файлу | Описание |
| :--- | :--- |
| `src/main.cpp` | Точка входа в программу, демонстрация работы моделей |
| `src/model.h` | Интерфейсы и структуры данных моделей |
| `src/model.cpp` | Реализация математических формул и логики |
| `test/unit_tests.cpp` | Модульные тесты (Google Test) |
| `CMakeLists.txt` | Конфигурация сборки и зависимостей |

## 3. Процесс сборки
Сборка проекта осуществлялась с использованием компилятора MSVC. В терминале PowerShell были выполнены следующие шаги:

1. Создание директории сборки: `mkdir build && cd build`
2. Генерация файлов сборки: `cmake ..`
3. Компиляция: `cmake --build .`

## 4. Результаты тестирования
Для верификации математических моделей использовалась утилита **CTest**. Все тесты успешно пройдены:

```text
1: [==========] Running 3 tests from 1 test suite.
1: [----------] 3 tests from ModelTestSuite
1: [ RUN      ] ModelTestSuite.LinearModelStandardCalculations
1: [       OK ] ModelTestSuite.LinearModelStandardCalculations (0 ms)
1: [ RUN      ] ModelTestSuite.LinearModelZeroInputs
1: [       OK ] ModelTestSuite.LinearModelZeroInputs (0 ms)
1: [ RUN      ] ModelTestSuite.NonlinearModelStandardCalculations
1: [       OK ] ModelTestSuite.NonlinearModelStandardCalculations (0 ms)
1: [----------] 3 tests from ModelTestSuite (0 ms total)
1: [  PASSED  ] 3 tests.
1/1 Test #1: RunAllProjectTests ...............   Passed    0.05 sec

100% tests passed out of 1
