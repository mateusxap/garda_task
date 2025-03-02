#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>

struct OperationMessage {
    uint8_t operation; // Код операции
    float operand1;    // Первый операнд
    float operand2;    // Второй операнд
};

std::vector<uint8_t> serialize(const OperationMessage& msg);

OperationMessage deserialize(const std::vector<uint8_t>& buffer);

float executeOperation(const OperationMessage& msg);