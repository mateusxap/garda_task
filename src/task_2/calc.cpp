#include "calc.hpp"

std::vector<uint8_t> serialize(const OperationMessage& msg) {
    std::vector<uint8_t> buffer(9); // Размер сообщения = 9 байт

    // Записываем тип операции
    buffer[0] = msg.operation;

    // Преобразуем float в байты для operand1
    const uint8_t* operand1_bytes = reinterpret_cast<const uint8_t*>(&msg.operand1);
    for (int i = 0; i < 4; ++i) {
        buffer[1 + i] = operand1_bytes[i];
    }

    // Преобразуем float в байты для operand2
    const uint8_t* operand2_bytes = reinterpret_cast<const uint8_t*>(&msg.operand2);
    for (int i = 0; i < 4; ++i) {
        buffer[5 + i] = operand2_bytes[i];
    }

    return buffer;
}

OperationMessage deserialize(const std::vector<uint8_t>& buffer) {
    if (buffer.size() != 9) {
        throw std::runtime_error("Неверный размер сообщения");
    }

    OperationMessage msg;
    msg.operation = buffer[0];

    // Проверяем корректность кода операции
    if (msg.operation > 3) {
        throw std::runtime_error("Недопустимый код операции");
    }

    // Извлекаем operand1
    msg.operand1 = *reinterpret_cast<const float*>(&buffer[1]);

    // Извлекаем operand2
    msg.operand2 = *reinterpret_cast<const float*>(&buffer[5]);

    return msg;
}

float executeOperation(const OperationMessage& msg) {
    switch (msg.operation) {
        case 0: // Сложение
            return msg.operand1 + msg.operand2;
        case 1: // Вычитание
            return msg.operand1 - msg.operand2;
        case 2: // Умножение
            return msg.operand1 * msg.operand2;
        case 3: // Деление
            if (msg.operand2 == 0.0f) {
                throw std::runtime_error("Деление на ноль");
            }
            return msg.operand1 / msg.operand2;
        default:
            throw std::runtime_error("Неизвестная операция");
    }
}