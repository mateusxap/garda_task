#!/bin/bash

# Переменные
SRC_DIR="src/task_1"
OUTPUT_DIR="bin"
ADD_SRC="$SRC_DIR/add.cpp"
TEST_SRC="$SRC_DIR/add_test.cpp"
ADD_EXEC="$OUTPUT_DIR/add"
TEST_EXEC="$OUTPUT_DIR/add_test"

# Создаём папку bin, если её нет
mkdir -p "$OUTPUT_DIR"

# Компиляция основной программы
echo "Сборка add.cpp..."
g++ -o "$ADD_EXEC" "$ADD_SRC" -std=c++17
if [ $? -eq 0 ]; then
    echo "Сборка add.cpp завершена успешно"
else
    echo "Ошибка при сборке add.cpp"
    exit 1
fi

# Компиляция тестов
echo "Сборка add_test.cpp..."
g++ -o "$TEST_EXEC" "$TEST_SRC" -lgtest -lgtest_main -pthread -std=c++17
if [ $? -eq 0 ]; then
    echo "Сборка add_test.cpp завершена успешно"
else
    echo "Ошибка при сборке add_test.cpp"
    exit 1
fi

# Запуск тестов
echo "Запуск тестов..."
"$TEST_EXEC"