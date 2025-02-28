#include <gtest/gtest.h>
#include <limits>
#include "add.cpp"  // Подключаем шаблонную функцию

TEST(AddTest, IntBasic) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_THROW(add(std::numeric_limits<int>::max(), 1), std::overflow_error);
}

TEST(AddTest, FloatBasic) {
    EXPECT_FLOAT_EQ(add(2.5f, 3.5f), 6.0f);
}

TEST(AddTest, DoubleBasic) {
    EXPECT_DOUBLE_EQ(add(2.5, 3.5), 6.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}