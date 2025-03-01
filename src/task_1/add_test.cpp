#include <gtest/gtest.h>
#include <limits>
#include "add.hpp"

// Базовые тесты для int
TEST(AddTest, IntBasic) {
    EXPECT_EQ(add(2, 3), 5);               // Простое сложение
    EXPECT_EQ(add(-5, 7), 2);              // Положительное + отрицательное
    EXPECT_EQ(add(-10, -5), -15);          // Два отрицательных
    EXPECT_EQ(add(0, 0), 0);               // Два нуля
}

// Тесты переполнения для int
TEST(AddTest, IntOverflow) {
    EXPECT_THROW(add(std::numeric_limits<int>::max(), 1), std::overflow_error);      // INT_MAX + 1
    EXPECT_THROW(add(std::numeric_limits<int>::min(), -1), std::overflow_error);     // INT_MIN - 1
    EXPECT_NO_THROW(add(std::numeric_limits<int>::max(), 0));                        // INT_MAX + 0 (без переполнения)
    EXPECT_NO_THROW(add(std::numeric_limits<int>::min(), 0));                        // INT_MIN + 0 (без переполнения)
}

// Тесты для больших чисел (без переполнения)
TEST(AddTest, IntLargeNumbers) {
    EXPECT_EQ(add(1000000, 2000000), 3000000);  // Большие положительные
    EXPECT_EQ(add(-1000000, -2000000), -3000000);  // Большие отрицательные
}

// Тесты для float
TEST(AddTest, FloatBasic) {
    EXPECT_FLOAT_EQ(add(2.5f, 3.5f), 6.0f);      // Простое сложение
    EXPECT_FLOAT_EQ(add(-1.5f, 2.5f), 1.0f);     // Отрицательное + положительное
    EXPECT_FLOAT_EQ(add(0.0f, 0.0f), 0.0f);      // Два нуля
    EXPECT_FLOAT_EQ(add(-2.75f, -3.25f), -6.0f); // Два отрицательных
}

// Тесты для float с высокой точностью
TEST(AddTest, FloatPrecision) {
    EXPECT_FLOAT_EQ(add(0.1f, 0.2f), 0.3f);      // Малые числа (проверка точности)
    EXPECT_FLOAT_EQ(add(1e6f, 1e-6f), 1000000.000001f);  // Большое + малое
}

// Тесты для double
TEST(AddTest, DoubleBasic) {
    EXPECT_DOUBLE_EQ(add(2.5, 3.5), 6.0);         // Простое сложение
    EXPECT_DOUBLE_EQ(add(-1.5, 2.5), 1.0);        // Отрицательное + положительное
    EXPECT_DOUBLE_EQ(add(0.0, 0.0), 0.0);         // Два нуля
    EXPECT_DOUBLE_EQ(add(-2.75, -3.25), -6.0);    // Два отрицательных
}

// Тесты для double с высокой точностью
TEST(AddTest, DoublePrecision) {
    EXPECT_DOUBLE_EQ(add(0.1, 0.2), 0.3);         // Малые числа (проверка точности)
    EXPECT_DOUBLE_EQ(add(1e10, 1e-10), 10000000000.0000000001);  // Большое + малое
}

// Тесты для long long (дополнительный тип)
TEST(AddTest, LongLongBasic) {
    EXPECT_EQ(add(1000000000LL, 2000000000LL), 3000000000LL);  // Большие числа
    EXPECT_THROW(add(std::numeric_limits<long long>::max(), 1LL), std::overflow_error);  // Переполнение
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}