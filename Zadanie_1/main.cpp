#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

// Лабораторная работа № 2. Вариант 2. Задание 1.
// Сортировка по убыванию и замена элементов с индексами 0, 2, 4, ...

void printVector(const std::vector<int>& values) {
    if (values.empty()) {
        std::cout << "(empty)";
    } else {
        for (std::size_t i = 0; i < values.size(); ++i) {
            if (i > 0) {
                std::cout << ' ';
            }
            std::cout << values[i];
        }
    }
    std::cout << '\n';
}

int main() {
    std::cout << "Lab 2. Variant 2. Task 1\n";
    std::cout << "Enter the number of elements (1 to 1000000): ";

    long long inputCount = 0;
    if (!(std::cin >> inputCount) || inputCount < 1 || inputCount > 1000000) {
        std::cerr << "Error: invalid number of elements.\n";
        return 1;
    }

    const std::size_t n = static_cast<std::size_t>(inputCount);
    std::vector<int> values(n);

    std::cout << "Enter " << n << " integer values:\n";
    for (std::size_t i = 0; i < n; ++i) {
        if (!(std::cin >> values[i])) {
            std::cerr << "Error: invalid integer at position " << (i + 1) << ".\n";
            return 1;
        }
    }

    std::cout << "\nOriginal vector: ";
    printVector(values);

    // Сортируем вектор по убыванию.
    std::sort(values.begin(), values.end(), std::greater<int>());
    std::cout << "Sorted vector:   ";
    printVector(values);

    // Для чётного индекса записываем порядковый номер (индекс + 1).
    for (std::size_t i = 0; i < values.size(); i += 2) {
        values[i] = static_cast<int>(i + 1);
    }

    std::cout << "Modified vector: ";
    printVector(values);
    std::cout << "Program completed successfully.\n";
    return 0;
}
