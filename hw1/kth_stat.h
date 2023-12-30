#ifndef KTH
#define KTH

template <typename T>
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
int Partition(T* left, T* right) {
  int sz = right - left;
  T pivot = *(right);
  int i = -1;
  for (int j = 0; j < sz; ++j) {
    if (*(left + j) < pivot) {
      i += 1;
      swap(*(left + i), *(left + j));
    }
  }
  swap(*(left + i + 1), *right);
  return i + 1;
}

template <typename T>
void RE_KthElement(T* left, T* kth, T* right) {
  if (right - left < 1) {
    return;
  }
  int partition = Partition(left, right);
  if (partition == (kth - left)) {
    return;
  }
  if ((kth - left) < partition) {
    RE_KthElement(left, kth, left + partition - 1);
  }
  RE_KthElement(left + partition + 1, kth, right);
}

template <typename T>
void KthElement(T* left, T* kth, T* right) {
  RE_KthElement(left, kth, right - 1);
}

#endif