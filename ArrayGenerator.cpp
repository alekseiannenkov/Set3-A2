//
// Created by Алексей on 23.11.2024.
//
#include <algorithm>
#include <random>
#include <vector>
class ArrayGenerator {
public:
  std::mt19937 mt;
  int minInt = 0;
  int maxInt = 6000;
  int arraySizes = 10000;

  std::vector<int> random;
  std::vector<int> reversed;
  std::vector<int> sorted;


  // Создание массивов по 10000 элементов, из которых потом будут
  // получаться путем копирования другие массивы.
  ArrayGenerator(int n) : mt(n), random(arraySizes),
  reversed(arraySizes), sorted(arraySizes) {
    int d = maxInt - minInt;
    for (int i = 0; i < arraySizes; ++i) {
      random[i] = mt() % d - minInt;
      reversed[i] = mt() % d - minInt;
      sorted[i] = mt() % d - minInt;
    }
    std::sort(reversed.begin(), reversed.end(), std::greater<>());
    std::sort(sorted.begin(), sorted.end());
    for (int i = 0; i < 3; ++i) {
      std::swap(sorted[mt() % arraySizes],
  sorted[mt() % arraySizes]);
    }
  }


  // Генерация случайного вектора
  std::vector<int> generateVector(int size) {
    std::vector<int> v = std::vector<int>(size);
    int d = mt() % (arraySizes - size);

    std::copy(random.begin() + d, random.begin() + d + size, v.begin());
    return v;
  }

  // Генерация отсортированного в обратном порядке вектора.
  std::vector<int> generateReversed(int size) {
    std::vector<int> v = std::vector<int>(size);
    int d = mt() % (arraySizes - size);

    std::copy(reversed.begin() + d,
      reversed.begin() + d + size, v.begin());
    return v;
  }


  // Генерация почти отсортированного вектора
  std::vector<int> generateAlmostSorted(int size) {
    std::vector<int> v = std::vector<int>(size);
    int d = mt() % (arraySizes - size);

    std::copy(sorted.begin() + d,
      sorted.begin() + d + size, v.begin());
    for (int i = 0; i < 5; ++i) {
      std::swap(v[mt() % size], v[mt() % size]);
    }
    return v;
  }

};
