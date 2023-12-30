#ifndef C__ALGO_CLION__SORT_H_
#define C__ALGO_CLION__SORT_H_

template <typename T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

// функция поддерживает свойство max-heap
template <typename T>
void Heapify(T* arr, int index, int len) {  // max_heap, стартуем с index, заканчиваем len
  int largest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < len && *(arr + largest) < *(arr + left)) {
    largest = left;
  }
  if (right < len && *(arr + largest) < *(arr + right)) {
    largest = right;
  }
  if (largest != index) {
    Swap(*(arr + index), *(arr + largest));
    Heapify(arr, largest, len);
  }
}

// массив превращает в кучу
template <typename T>
void DoHeap(T* left, int len) {
  int last_subtree = len / 2 - 1;

  for (int i = last_subtree; i >= 0; i--) {
    Heapify(left, i, len);
  }
}

// Чисто для контеста
template <typename T>
void MakeHeap(T* begin, T* end) {
  int len = begin - end;
  DoHeap(begin, len);
}

template <typename T>
void RealSort(T* left, T* right) {
  int len = right - left + 1;
  DoHeap(left, len);
  for (int i = len - 1; i >= 0; i--) {
    Swap(*left, *(left + i));
    // вызываем heapify на уменьшенной куче
    Heapify(left, 0, i);
  }
}

template <typename T>
void SortHeap(T* left, T* right) {  // делаем полуинтервал
  RealSort(left, right - 1);
}

#endif