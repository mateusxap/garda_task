#include <gtest/gtest.h>
#include "calc.hpp"

// Тест сериализации и десериализации
TEST(CalcTest, SerializeDeserialize) {
    OperationMessage msg{2, 5.0f, 3.0f}; // Пример: 5.0 * 3.0
    std::vector<uint8_t> buffer = serialize(msg);
    OperationMessage received = deserialize(buffer);

    EXPECT_EQ(received.operation, msg.operation); // Проверка кода операции
    EXPECT_FLOAT_EQ(received.operand1, msg.operand1); // Проверка первого операнда
    EXPECT_FLOAT_EQ(received.operand2, msg.operand2); // Проверка второго операнда
    EXPECT_EQ(buffer.size(), 9); // Проверка размера буфера
}

// Тест операции сложения
TEST(CalcTest, Addition) {
    OperationMessage msg{0, 3.5f, 2.7f}; // 3.5 + 2.7
    EXPECT_FLOAT_EQ(executeOperation(msg), 6.2f);

    std::vector<uint8_t> buffer = serialize(msg);
    OperationMessage received = deserialize(buffer);
    EXPECT_FLOAT_EQ(executeOperation(received), 6.2f);
}

// Тест операции вычитания
TEST(CalcTest, Subtraction) {
    OperationMessage msg{1, 5.0f, 2.0f}; // 5.0 - 2.0
    EXPECT_FLOAT_EQ(executeOperation(msg), 3.0f);

    std::vector<uint8_t> buffer = serialize(msg);
    OperationMessage received = deserialize(buffer);
    EXPECT_FLOAT_EQ(executeOperation(received), 3.0f);
}

// Тест операции умножения
TEST(CalcTest, Multiplication) {
    OperationMessage msg{2, 4.0f, 3.0f}; // 4.0 * 3.0
    EXPECT_FLOAT_EQ(executeOperation(msg), 12.0f);

    std::vector<uint8_t> buffer = serialize(msg);
    OperationMessage received = deserialize(buffer);
    EXPECT_FLOAT_EQ(executeOperation(received), 12.0f);
}

// Тест операции деления
TEST(CalcTest, Division) {
    OperationMessage msg{3, 6.0f, 2.0f}; // 6.0 / 2.0
    EXPECT_FLOAT_EQ(executeOperation(msg), 3.0f);

    std::vector<uint8_t> buffer = serialize(msg);
    OperationMessage received = deserialize(buffer);
    EXPECT_FLOAT_EQ(executeOperation(received), 3.0f);
}

// Тест деления на ноль
TEST(CalcTest, DivisionByZero) {
    OperationMessage msg{3, 6.0f, 0.0f}; // 6.0 / 0.0
    EXPECT_THROW(executeOperation(msg), std::runtime_error);

    std::vector<uint8_t> buffer = serialize(msg);
    OperationMessage received = deserialize(buffer);
    EXPECT_THROW(executeOperation(received), std::runtime_error);
}

// Тест некорректного кода операции
TEST(CalcTest, InvalidOperationCode) {
    std::vector<uint8_t> invalid_buffer = {4, 0, 0, 0, 0, 0, 0, 0, 0}; // Код 4 недопустим
    EXPECT_THROW(deserialize(invalid_buffer), std::runtime_error);
}

// Тест некорректного размера буфера
TEST(CalcTest, InvalidBufferSize) {
    std::vector<uint8_t> short_buffer = {0, 1, 2}; // Слишком короткий буфер
    EXPECT_THROW(deserialize(short_buffer), std::runtime_error);

    std::vector<uint8_t> long_buffer(10, 0); // Слишком длинный буфер
    EXPECT_THROW(deserialize(long_buffer), std::runtime_error);
}

// Тест граничных значений для float
TEST(CalcTest, FloatBoundaryValues) {
    OperationMessage msg_max{0, std::numeric_limits<float>::max(), 0.0f}; // FLT_MAX + 0
    EXPECT_FLOAT_EQ(executeOperation(msg_max), std::numeric_limits<float>::max());

    OperationMessage msg_min{0, -std::numeric_limits<float>::max(), 0.0f}; // -FLT_MAX + 0
    EXPECT_FLOAT_EQ(executeOperation(msg_min), -std::numeric_limits<float>::max());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}