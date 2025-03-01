#include <limits>
#include <stdexcept>
#include <type_traits>
#include <iostream>

template <typename T>
T add(T a, T b) {
    if constexpr (std::is_integral<T>::value) {  // Проверка на этапе компиляци на целочисленный тип
        if (a > 0 && b > 0 && a > std::numeric_limits<T>::max() - b) {          //  std::numeric_limits<T>::max() - b вычисляет, какое максимальное
            throw std::overflow_error("Переполнение при сложении целых чисел"); // значение может быть добавлено к b, чтобы не превысить предел типа T
        }
        if (a < 0 && b < 0 && a < std::numeric_limits<T>::min() - b) {
            throw std::overflow_error("Переполнение при сложении целых чисел");
        }
    }
    return a + b;
}
