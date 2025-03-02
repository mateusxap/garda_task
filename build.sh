#!/bin/bash

# Переменные
SRC_DIR="src"
OUTPUT_DIR="bin"
# Task 1
TASK1_DIR="$SRC_DIR/task_1"
ADD_SRC="$TASK1_DIR/add.cpp"  # Реализация для task_1
TEST1_SRC="$TASK1_DIR/add_test.cpp"
TEST1_EXEC="$OUTPUT_DIR/add_test"
# Task 2
TASK2_DIR="$SRC_DIR/task_2"
CALC_SRC="$TASK2_DIR/calc.cpp"  # Реализация для task_2
TEST2_SRC="$TASK2_DIR/calc_test.cpp"
TEST2_EXEC="$OUTPUT_DIR/calc_test"

# Создаём папку bin, если её нет
mkdir -p "$OUTPUT_DIR"

# Проверяем права на запись
if [ ! -w "$OUTPUT_DIR" ]; then
    echo "Ошибка: Нет прав на записи в $OUTPUT_DIR. Попробуйте 'chmod u+w $OUTPUT_DIR'"
    exit 1
fi

# Компиляция Task 1: тесты (add_test.cpp + add.cpp)
echo "Сборка add_test.cpp (Task 1)..."
g++ -o "$TEST1_EXEC" "$TEST1_SRC" "$ADD_SRC" -lgtest -lgtest_main -pthread -std=c++17
if [ $? -eq 0 ]; then
    echo "Сборка add_test.cpp завершена успешно"
else
    echo "Ошибка при сборке add_test.cpp"
    exit 1
fi

# Компиляция Task 2: тесты (calc_test.cpp + calc.cpp)
echo "Сборка calc_test.cpp (Task 2)..."
g++ -o "$TEST2_EXEC" "$TEST2_SRC" "$CALC_SRC" -lgtest -lgtest_main -pthread -std=c++17
if [ $? -eq 0 ]; then
    echo "Сборка calc_test.cpp завершена успешно"
else
    echo "Ошибка при сборке calc_test.cpp"
    exit 1
fi

# Запуск тестов Task 1
echo "Запуск тестов Task 1..."
"$TEST1_EXEC"

# Запуск тестов Task 2
echo "Запуск тестов Task 2..."
"$TEST2_EXEC"