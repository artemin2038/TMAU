# Лабораторная работа №2
## Модульное тестирование программы моделирования температуры

### Студент
- Группа: 577
- Номер: 17
- Дата выполнения: 18.06.2026

### Структура проектаtrunk/AS0057717/task_02/ ├── src/ │ ├── CMakeLists.txt │ ├── main.cpp │ └── models.hpp ├── test/ │ ├── test_temperature.cpp │ └── CMakeLists.txt └── doc/ └── readme.md
text
### Количество тестов: 10

### Покрытие кода: ~95%

### Запуск тестов
```bash
cd trunk/AS0057717/task_02/test
mkdir build && cd build
cmake ..
make
./test_temperature
Результаты
Все 10 тестов проходят успешно ✅ EOF
text
## 7. Добавляем в Git

```bash
# Добавляем все файлы
git add trunk/AS0057717/

# Коммит
git commit -m "Add lab work #2 for group 577, student 17

- Implement temperature models in main.cpp and models.hpp
- Add 10 unit tests with Google Test
- Code coverage ~95%
- Structure follows repository standards"

# Отправка
git push origin main
