#include <iostream>

template <typename T>
bool BinarySearch(const T* begin, const T* end, const T& target) {
  int right = end - begin;
  int left = -1;
  while (left + 1 < right) {
    int mid = (left + right) / 2;
    if (!(target < *(begin + mid)) && !(*(begin + mid) < target)) {
      return true;
    }
    if (*(begin + mid) < target) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return false;
}

template <typename T>
const T* LowerBound(const T* begin, const T* end, const T& target) {
  int left = -1;
  int right = end - begin;

  while (right - left > 1) {
    int mid = (right + left) / 2;
    if (!(*(begin + mid) < target)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  if (!(begin + right < end) && !(end < begin + right)) {
    return end;
  }
  if (!(*(begin + right) < target)) {
    return begin + right;
  }
  return end;
}

template <typename T>
const T* UpperBound(const T* begin, const T* end, const T& target) {
  int left = -1;
  int right = end - begin;

  while (right - left > 1) {
    int mid = (right + left) / 2;
    if (target < *(begin + mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  if (!(begin + right < end) && !(end < begin + right)) {
    return end;
  }
  if (target < *(begin + right)) {
    return begin + right;
  }
  return end;
}

int main() {
  int* arr = new int[5]{1, 2, 3, 4, 5};
  int a, b, c;
  for (int i = 0; i < 5; ++i) {
    std::cin >> a >> b >> c;
    std::cout << "- " << BinarySearch(arr + a, arr + b, c) << " " << *LowerBound(arr + a, arr + b, c) << " " << *UpperBound(arr + a, arr + b, c);
    std::cout << '\n';
  }
}