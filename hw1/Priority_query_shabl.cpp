// #ifndef PRIOR
// #define PRIOR
#include <iostream>

template <typename T>
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void SiftUp(T* begin, T* end) {
  int sz = end - begin;
  int temp = sz - 1;
  while (temp != 0 && *(begin + (temp - 1) / 2) < *(begin + temp)) {
    swap(*(begin + temp), *(begin + (temp - 1) / 2));
    temp = (temp - 1) / 2;
  }
}

template <typename T>
void SiftDown(T* begin, T* end) {
  int sz = end - begin;
  int greater = 0;
  int cur = 2 * greater + 1;
  while (cur < sz) {
    if (cur + 1 < sz && *(begin + cur) < *(begin + cur + 1)) {
      cur += 1;
    }

    if (!(*(begin + greater) < *(begin + cur))) {
      break;
    }

    swap(*(begin + greater), *(begin + cur));
    greater = cur;
    cur = 2 * greater + 1;
  }
}

// вставка end-1 элемента в пирамиду, восстанавливает пирамиду [begin, end)
template <typename T>
void PushHeap(T* begin, T* end) {
  SiftUp(begin, end);
}

// удаление корня, восстанавливает пирамиду [begin, end - 1)
template <typename T>
void PopHeap(T* begin, T* end) {
  swap(*begin, *(end - 1));
  SiftDown(begin, end - 1);
}

// #endif
int main() {
  int* arr = new int[7]{9, 5, 4, 1, 2, 3, 6};
  PushHeap(arr, arr + 7);
  for (int i = 0; i < 7; ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';
  PopHeap(arr, arr + 7);
  for (int i = 0; i < 7; ++i) {
    std::cout << arr[i] << ' ';
  }
}