//
// Created by Алексей on 23.11.2024.
//
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>
#include <iostream>

#include "ArrayGenerator.cpp"


void merge(std::vector<int> &vector,
  int leftBound, int mid, int rightBound) {

  std::vector<int> firstVector;
  std::vector<int> secondVector;

  for (int i = leftBound; i <= mid; ++i) {
    firstVector.push_back(vector[i]);
  }

  for (int i = mid + 1; i <= rightBound; ++i) {
    secondVector.push_back(vector[i]);
  }

  int first = 0;
  int second = 0;
  int element = leftBound;

  int firstSize = firstVector.size();
  int secondSize = secondVector.size();
  while (first < firstSize && second < secondSize) {
    if (firstVector[first] <= secondVector[second]) {
      vector[element++] = firstVector[first++];

    } else {
      vector[element++] = secondVector[second++];
    }
  }

  while (first < firstSize) {
    vector[element++] = firstVector[first++];
  }

  while (second < secondSize) {
    vector[element++] = secondVector[second++];
  }
}

void mergeSort(std::vector<int> &vect,
  int leftBound, int rightBound) {

  if (rightBound - leftBound <= 1) {
    if (vect[rightBound] < vect[leftBound]) {
      std::swap(vect[rightBound], vect[leftBound]);

    }
    return;
  }

  int middle = (leftBound + rightBound) / 2;

  mergeSort(vect, leftBound, middle);
  mergeSort(vect, middle + 1, rightBound);

  merge(vect, leftBound, middle, rightBound);
}

void print_vector(std::vector<int> v) {
  for (auto el: v) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void insertionSort(std::vector<int> &v,
  int leftBound, int rightBound) {
  for (int i = leftBound + 1; i <= rightBound; ++i) {
    int key = v[i];
    int j = i - 1;
    while (j >= leftBound && v[j] > key) {
      v[j + 1] = v[j];
      --j;
    }
    v[j + 1] = key;
  }
}

void hybridSort(std::vector<int> &vect,
  int leftBound, int rightBound, int switchNumber) {
  if (rightBound - leftBound <= switchNumber) {
    insertionSort(vect, leftBound, rightBound);
    return;
  }

  int middle = (leftBound + rightBound) / 2;

  hybridSort(vect, leftBound, middle, switchNumber);
  hybridSort(vect, middle + 1, rightBound, switchNumber);

  merge(vect, leftBound, middle, rightBound);
}

class SortTester {
  public:
  // Замерение merge sort на рандомных массивах
  void random_merge(std::string mergeFilePath, ArrayGenerator arrG) {
    std::ofstream mergeFile;
    mergeFile.open(mergeFilePath);
    mergeFile << "x;y\n";
    for (int i = 500; i < 10000; i += 100) {
      long long mergeTime = 0;
      std::vector<int> inputVector = arrG.generateVector(i);
      std::vector<int> v;
      for (int j = 0; j < 10; ++j) {
        v = inputVector;
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(v, 0, i - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        mergeTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      }
      mergeFile << i << ';' << mergeTime << '\n';
    }
    mergeFile.close();
  }

  // Замерение hybrid sort на рандомных массивах
  void random_hybrid(std::string hybridFilePath, int switchNumber, ArrayGenerator arrG) {
    std::ofstream hybridFile;
    hybridFile.open(hybridFilePath);
    hybridFile << "x;y\n";
    for (int i = 500; i < 10000; i += 100) {
      long long hybridTime = 0;
      std::vector<int> inputVector = arrG.generateVector(i);
      std::vector<int> v;
      for (int j = 0; j < 10; ++j) {
        v = inputVector;
        auto start = std::chrono::high_resolution_clock::now();
        hybridSort(v, 0, i - 1, switchNumber);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        hybridTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      }
      hybridFile << i << ';' << hybridTime << '\n';
    }
    hybridFile.close();
  }

  // Замерение merge sort на отсортированных в обратном порядке массивах
  void reverse_merge(std::string mergeFilePath, ArrayGenerator arrG) {
    std::ofstream mergeFile;
    mergeFile.open(mergeFilePath);
    mergeFile << "x;y\n";
    for (int i = 500; i < 10000; i += 100) {
      long long mergeTime = 0;
      std::vector<int> inputVector = arrG.generateReversed(i);
      std::vector<int> v;
      for (int j = 0; j < 10; ++j) {
        v = inputVector;
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(v, 0, i - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        mergeTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      }
      mergeFile << i << ';' << mergeTime << '\n';
    }
    mergeFile.close();
  }

  // Замерение hybrid sort на отсортированных в обратном порядке массивах
  void reverse_hybrid(std::string hybridFilePath, int switchNumber, ArrayGenerator arrG) {
    std::ofstream hybridFile;
    hybridFile.open(hybridFilePath);
    hybridFile << "x;y\n";
    for (int i = 500; i < 10000; i += 100) {
      long long hybridTime = 0;
      std::vector<int> inputVector = arrG.generateReversed(i);
      std::vector<int> v;
      for (int j = 0; j < 10; ++j) {
        v = inputVector;
        auto start = std::chrono::high_resolution_clock::now();
        hybridSort(v, 0, i - 1, switchNumber);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        hybridTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      }
      hybridFile << i << ';' << hybridTime << '\n';
    }
    hybridFile.close();
  }

  // Замерение merge sort на почти отсортированных массивах
  void almostSorted_merge(std::string mergeFilePath, ArrayGenerator arrG) {
    std::ofstream mergeFile;
    mergeFile.open(mergeFilePath);
    mergeFile << "x;y\n";
    for (int i = 500; i < 10000; i += 100) {
      long long mergeTime = 0;
      std::vector<int> inputVector = arrG.generateAlmostSorted(i);
      std::vector<int> v;
      for (int j = 0; j < 10; ++j) {
        v = inputVector;
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(v, 0, i - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        mergeTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      }
      mergeFile << i << ';' << mergeTime << '\n';
    }
    mergeFile.close();
  }

  // Замерение hybrid sort на почти отсортированных массивах
  void almostSorted_hybrid(std::string hybridFilePath, int switchNumber, ArrayGenerator arrG) {
    std::ofstream hybridFile;
    hybridFile.open(hybridFilePath);
    hybridFile << "x;y\n";
    for (int i = 500; i < 10000; i += 100) {
      long long hybridTime = 0;
      std::vector<int> inputVector = arrG.generateAlmostSorted(i);
      std::vector<int> v;
      for (int j = 0; j < 10; ++j) {
        v = inputVector;
        auto start = std::chrono::high_resolution_clock::now();
        hybridSort(v, 0, i - 1, switchNumber);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        hybridTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      }
      hybridFile << i << ';' << hybridTime << '\n';
    }
    hybridFile.close();
  }
};

int main() {
  SortTester tester = SortTester();
  ArrayGenerator arrG = ArrayGenerator(333);
  tester.random_merge("A2\\merge_random_over500.csv", arrG);
  tester.reverse_merge("A2\\merge_reversed_over500.csv", arrG);
  tester.almostSorted_merge("A2\\merge_almostSorted_over500.csv", arrG);
  for (int i = 5; i <= 50; i += 5) {
    tester.random_hybrid("A2\\hybrid_random_" + std::to_string(i) +  "_over500.csv", i, arrG);
    tester.reverse_hybrid("A2\\hybrid_reversed_" + std::to_string(i) +  "_over500.csv", i, arrG);
    tester.almostSorted_hybrid("A2\\hybrid_almostSorted_" + std::to_string(i) +  "_over500.csv", i, arrG);
  }

}