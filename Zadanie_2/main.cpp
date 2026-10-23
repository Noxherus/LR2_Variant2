#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

// Лабораторная работа № 2. Вариант 2. Задание 2.
// Векторы: первая половина, средняя треть, средние значения и подсчёт пар.

using IntVector = std::vector<int>;

// Возвращает первую половину и среднюю треть исходного вектора.
// Для длины, не кратной 2 или 3, используются целые части от деления.
std::pair<IntVector, IntVector> part(const IntVector& values) {
    const std::size_t n = values.size();
    const std::size_t halfSize = n / 2;
    const std::size_t thirdSize = n / 3;
    const std::size_t thirdStart = (n - thirdSize) / 2;

    const auto firstEnd = std::next(values.cbegin(),
                                    static_cast<std::ptrdiff_t>(halfSize));
    const auto middleStart = std::next(values.cbegin(),
                                      static_cast<std::ptrdiff_t>(thirdStart));
    const auto middleEnd = std::next(middleStart,
                                    static_cast<std::ptrdiff_t>(thirdSize));

    return {
        IntVector(values.cbegin(), firstEnd),
        IntVector(middleStart, middleEnd)
    };
}

void printVector(const char* label, const IntVector& values) {
    std::cout << label;
    if (values.empty()) {
        std::cout << "(empty)";
    } else {
        for (auto it = values.cbegin(); it != values.cend(); ++it) {
            if (it != values.cbegin()) {
                std::cout << ' ';
            }
            std::cout << *it;
        }
    }
    std::cout << '\n';
}

void printAverage(const char* label, const IntVector& values) {
    std::cout << label;
    if (values.empty()) {
        std::cout << "undefined (empty vector)\n";
        return;
    }

    const std::int64_t total = std::accumulate(values.cbegin(), values.cend(),
                                               std::int64_t{0});
    const double average = static_cast<double>(total) / values.size();
    std::cout << std::fixed << std::setprecision(2) << average << '\n';
}

// Ищем максимальный элемент исходного вектора, кратный 17.
struct MultipleOf17 {
    bool found = false;
    int value = 0;
};

MultipleOf17 findMaximumMultipleOf17(const IntVector& values) {
    MultipleOf17 result;
    for (int number : values) {
        if (number % 17 == 0 && (!result.found || number > result.value)) {
            result.found = true;
            result.value = number;
        }
    }
    return result;
}

// Подсчитываем пары элементов с разными индексами i < j.
// Сортировка и два указателя дают сложность O(n log n).
std::uint64_t countPairsAbove(const IntVector& values, int limit) {
    if (values.size() < 2) {
        return 0;
    }

    IntVector sorted = values;
    std::sort(sorted.begin(), sorted.end());

    std::size_t left = 0;
    std::size_t right = sorted.size() - 1;
    std::uint64_t count = 0;

    while (left < right) {
        const std::int64_t sum = static_cast<std::int64_t>(sorted[left])
                               + static_cast<std::int64_t>(sorted[right]);
        if (sum > limit) {
            // Все элементы от left до right - 1 дают подходящую пару с right.
            count += static_cast<std::uint64_t>(right - left);
            --right;
        } else {
            ++left;
        }
    }
    return count;
}

int main() {
    std::cout << "Lab 2. Variant 2. Task 2\n";
    std::cout << "Enter the number of elements (1 to 1000000): ";

    long long inputCount = 0;
    if (!(std::cin >> inputCount) || inputCount < 1 || inputCount > 1000000) {
        std::cerr << "Error: invalid number of elements.\n";
        return 1;
    }

    const std::size_t n = static_cast<std::size_t>(inputCount);
    IntVector values(n);
    std::cout << "Enter " << n << " integer values:\n";
    for (std::size_t i = 0; i < n; ++i) {
        if (!(std::cin >> values[i])) {
            std::cerr << "Error: invalid integer at position " << (i + 1) << ".\n";
            return 1;
        }
    }

    const auto portions = part(values);
    const IntVector& firstHalf = portions.first;
    const IntVector& middleThird = portions.second;

    std::cout << "\nRESULTS\n";
    printVector("Original vector: ", values);
    printVector("First half:      ", firstHalf);
    printVector("Middle third:    ", middleThird);
    printAverage("Average of first half:   ", firstHalf);
    printAverage("Average of middle third: ", middleThird);

    const MultipleOf17 maximum = findMaximumMultipleOf17(values);
    if (!maximum.found) {
        std::cout << "No multiple of 17 was found in the original vector.\n";
        std::cout << "Pair counts cannot be calculated without this threshold.\n";
        std::cout << "Program completed successfully.\n";
        return 0;
    }

    std::cout << "Maximum multiple of 17: " << maximum.value << '\n';
    std::cout << "Pairs in first half with sum > " << maximum.value << ": "
              << countPairsAbove(firstHalf, maximum.value) << '\n';
    std::cout << "Pairs in middle third with sum > " << maximum.value << ": "
              << countPairsAbove(middleThird, maximum.value) << '\n';
    std::cout << "Program completed successfully.\n";
    return 0;
}
