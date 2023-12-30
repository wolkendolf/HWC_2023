#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
template <typename T, const size_t N>
struct Array {
  T arr[N];

  T& operator[](const size_t index) {
    return *(arr + index);
  }

  const T& operator[](size_t index) const {
    return *(arr + index);
  }

  T& Front() {
    return *arr;
  }

  T& Back() {
    return *(arr + N - 1);
  }

  T* Data() {
    return arr;
  }

  const T& Front() const {
    return *arr;
  }
  const T& Back() const {
    return *(arr + N - 1);
  }
  const T* Data() const {
    return arr;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return Size() <= 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = value;
    }
  }

  void HelpSwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < this->Size(); ++i) {
      HelpSwap(arr[i], other[i]);
    }
  }
};

#endif