#!/bin/bash

# Переменные
SRC_DIR="src/task_1"
OUTPUT_DIR="bin"
ADD_SRC="$SRC_DIR/add.cpp"
TEST_SRC="$SRC_DIR/add_test.cpp"
TEST_EXEC="$OUTPUT_DIR/add_test"

# Создаём папку bin, если её нет
mkdir -p "$OUTPUT_DIR"

# Проверяем права на запись
if [ ! -w "$OUTPUT_DIR" ]; then
    echo "Ошибка: Нет прав на запись в $OUTPUT_DIR. Попробуйте 'chmod u+w $OUTPUT_DIR'"
    exit 1
fi

# Компиляция тестов (включая add.cpp)
echo "Сборка add_test.cpp с add.cpp..."
g++ -o "$TEST_EXEC" "$TEST_SRC" "$ADD_SRC" -lgtest -lgtest_main -pthread -std=c++17
if [ $? -eq 0 ]; then
    echo "Сборка завершена успешно"
else
    echo "Ошибка при сборке"
    exit 1
fi

# Запуск тестов
echo "Запуск тестов..."
"$TEST_EXEC"
