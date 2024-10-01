#ifndef VECTOR
#define VECTOR

#include <memory>
#include <cstddef>
#include <iterator>

#define VECTOR_MEMORY_IMPLEMENTED

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T>
class Vector {
  T* data_;
  size_t size_{};
  size_t capacity_;

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;

  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector();
  explicit Vector(size_t size);
  Vector(size_t size, const T& value);

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator begin, Iterator end) {
    if (std::distance(begin, end) < 1) {
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    } else {
      auto size = static_cast<size_t>(std::distance(begin, end));
      auto new_data = static_cast<T*>(operator new(size * sizeof(T)));
      size_t i = 0;
      try {
        while (i < size) {
          new (new_data + i) T(*(std::next(begin, i)));
          ++i;
        }
      } catch (...) {
        ClearInterval(0, i + 1, new_data);
        operator delete(new_data);
        throw;
      }
      data_ = new_data;
      size_ = size;
      capacity_ = size;
    }
  }

  Vector(std::initializer_list<T>);

  // правило пяти
  Vector(const Vector<T>&);
  Vector(Vector<T>&&);
  Vector& operator=(const Vector<T>&);
  Vector& operator=(Vector<T>&&);
  ~Vector();

  size_t Size() const noexcept;
  size_t Capacity() const;
  bool Empty() const;

  const T& operator[](size_t) const;
  T& operator[](size_t);

  const T& At(size_t) const;
  T& At(size_t);

  const T& Front() const;
  T& Front();

  const T& Back() const;
  T& Back();

  const T* Data() const;
  T* Data();

  void Swap(Vector<T>&);

  void Resize(size_t, T&&);
  void Resize(size_t);
  void Reserve(size_t);
  void ShrinkToFit();

  void ClearInterval(size_t begin, size_t end, T*& data);
  void Clear();

  void PushBack(const T&);
  void PushBack(T&&);
  void PopBack();

  template <typename... Args>
  void EmplaceBack(Args&&... args) {
    this->PushBack(T(std::forward<Args>(args)...));
  }

  template <class M>
  friend bool operator<(const Vector<M>&, const Vector<M>&);
  template <class M>
  friend bool operator>(const Vector<M>&, const Vector<M>&);
  template <class M>
  friend bool operator<=(const Vector<M>&, const Vector<M>&);
  template <class M>
  friend bool operator>=(const Vector<M>&, const Vector<M>&);
  template <class M>
  friend bool operator==(const Vector<M>&, const Vector<M>&);
  template <class M>
  friend bool operator!=(const Vector<M>&, const Vector<M>&);

  // iterators
  Iterator begin() {  //  NOLINT
    return static_cast<Iterator>(data_);
  }

  Iterator end() {  //  NOLINT
    return static_cast<Iterator>(data_ + size_);
  }

  ConstIterator begin() const {  //  NOLINT
    return static_cast<ConstIterator>(data_);
  }

  ConstIterator end() const {  //  NOLINT
    return static_cast<ConstIterator>(data_ + size_);
  }

  ConstIterator cbegin() const {  //  NOLINT
    return static_cast<ConstIterator>(data_);
  }

  ConstIterator cend() const {  //  NOLINT
    return static_cast<ConstIterator>(data_ + size_);
  }

  std::reverse_iterator<Iterator> rbegin() {  //  NOLINT
    return std::make_reverse_iterator(this->end());
  }

  std::reverse_iterator<Iterator> rend() {  //  NOLINT
    return std::make_reverse_iterator(this->begin());
  }

  std::reverse_iterator<ConstIterator> rbegin() const {  //  NOLINT
    return std::make_reverse_iterator(this->cend());
  }

  std::reverse_iterator<ConstIterator> rend() const {  //  NOLINT
    return std::make_reverse_iterator(this->cbegin());
  }

  std::reverse_iterator<ConstIterator> crbegin() const {  //  NOLINT
    return std::make_reverse_iterator(this->cend());
  }

  std::reverse_iterator<ConstIterator> crend() const {  //  NOLINT
    return std::make_reverse_iterator(this->cbegin());
  }
};

template <class T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {
}

template <class T>
Vector<T>::Vector(size_t size) : Vector() {
  if (size != 0) {
    auto new_data = static_cast<T*>(operator new(size * sizeof(T)));
    size_t i = 0;
    try {
      while (i < size) {
        new (new_data + i) T{};
        ++i;
      }
    } catch (...) {
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    data_ = new_data;
    size_ = size;
    capacity_ = size;
  }
}

template <class T>
Vector<T>::Vector(size_t size, const T& value) : Vector() {
  if (size != 0) {
    auto new_data = static_cast<T*>(operator new(size * sizeof(T)));
    size_t i = 0;
    try {
      while (i < size) {
        new (new_data + i) T(value);
        ++i;
      }
    } catch (...) {
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    data_ = new_data;
    size_ = size;
    capacity_ = size;
  }
}

template <class T>
Vector<T>::Vector(std::initializer_list<ValueType> list) : Vector() {
  data_ = static_cast<T*>(operator new(list.size() * sizeof(T)));
  for (auto it = list.begin(); it != list.end(); ++it) {
    new (data_ + size_) ValueType(*it);
    ++size_;
  }
  capacity_ = list.size();
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
  if (other.size_ == 0) {
    data_ = nullptr;
    capacity_ = 0;
  } else {
    auto new_data = static_cast<T*>(operator new(sizeof(T) * other.capacity_));
    size_t i = 0;
    try {
      while (i < other.size_) {
        new (new_data + i) T(other[i]);
        ++i;
      }
    } catch (...) {
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;
  }
}

template <class T>
Vector<T>::Vector(Vector<T>&& other) : Vector() {
  Swap(other);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    auto new_vec = other;
    Swap(new_vec);
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
  auto new_vec = std::move(other);
  Swap(new_vec);
  return *this;
}

template <class T>
Vector<T>::~Vector() {
  ClearInterval(0, size_, data_);
  operator delete(data_);
}

template <class T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <class T>
size_t Vector<T>::Capacity() const {
  return capacity_;
}

template <class T>
bool Vector<T>::Empty() const {
  return size_ == 0;
}

template <class T>
const T& Vector<T>::operator[](size_t indx) const {
  return data_[indx];
}

template <class T>
T& Vector<T>::operator[](size_t indx) {
  return data_[indx];
}

template <class T>
const T& Vector<T>::At(size_t indx) const {
  if (indx > size_ - 1) {
    throw std::out_of_range("Out of range");
  }
  return data_[indx];
}

template <class T>
T& Vector<T>::At(size_t indx) {
  if (indx > size_ - 1) {
    throw std::out_of_range("Out of range");
  }
  return data_[indx];
}

template <class T>
const T& Vector<T>::Front() const {
  return data_[0];
}

template <class T>
T& Vector<T>::Front() {
  return data_[0];
}

template <class T>
const T& Vector<T>::Back() const {
  return data_[size_ - 1];
}

template <class T>
T& Vector<T>::Back() {
  return data_[size_ - 1];
}

template <class T>
const T* Vector<T>::Data() const {
  return data_;
}

template <class T>
T* Vector<T>::Data() {
  return data_;
}

template <class T>
void Vector<T>::Swap(Vector<T>& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <class T>
void Vector<T>::Resize(size_t new_size) {
  if (new_size > capacity_) {
    auto new_data = static_cast<T*>(operator new(new_size * sizeof(T)));
    size_t i = 0;
    try {
      while (i < size_) {
        new (new_data + i) T(std::move(data_[i]));
        ++i;
      }
      while (i < new_size) {
        new (new_data + i) T();
        ++i;
      }
    } catch (...) {
      for (size_t j = 0; j < size_; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    if (data_ != nullptr) {
      ClearInterval(0, size_, data_);
      operator delete(data_);
    }
    data_ = new_data;
    capacity_ = new_size;
  } else if (new_size > size_) {
    size_t i = size_;
    try {
      while (i < new_size) {
        new (data_ + i) T{};
        ++i;
      }
    } catch (...) {
      ClearInterval(new_size, i, data_);
      throw;
    }
  } else {
    ClearInterval(new_size, size_, data_);
  }
  size_ = new_size;
}

template <class T>
void Vector<T>::Resize(size_t new_size, T&& value) {
  if (new_size > capacity_) {
    auto new_data = static_cast<T*>(operator new(sizeof(T) * new_size));
    size_t i = 0;
    try {
      while (i < size_) {
        new (new_data + i) T(std::move(data_[i]));
        ++i;
      }
      while (i < new_size) {
        new (new_data + i) T(std::move(value));
        ++i;
      }
    } catch (...) {
      for (size_t j = 0; j < size_; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    if (data_ != nullptr) {
      ClearInterval(0, size_, data_);
      operator delete(data_);
    }
    data_ = new_data;
    capacity_ = new_size;
  } else if (new_size > size_) {
    size_t i = size_;
    try {
      while (i < new_size) {
        new (data_ + i) T(std::move(value));
        ++i;
      }
    } catch (...) {
      ClearInterval(size_, i, data_);
      throw;
    }
  } else {
    ClearInterval(new_size, size_, data_);
  }
  size_ = new_size;
}

template <class T>
void Vector<T>::Reserve(size_t new_capacity) {
  if (new_capacity > capacity_) {
    auto new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
    size_t i = 0;
    try {
      while (i < size_) {
        new (new_data + i) T(std::move(data_[i]));
        ++i;
      }
    } catch (...) {
      for (size_t j = 0; j <= i; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }

    if (data_ != nullptr) {
      ClearInterval(0, size_, data_);
      operator delete(data_);
    }
    data_ = new_data;
    capacity_ = new_capacity;
  }
}

template <class T>
void Vector<T>::ShrinkToFit() {
  if (size_ == 0) {
    operator delete(data_);
    capacity_ = 0;
    data_ = nullptr;
  } else {
    auto new_data = static_cast<T*>(operator new(size_ * sizeof(T)));
    size_t i = 0;
    while (i < size_) {
      new (new_data + i) T(std::move(data_[i]));
      ++i;
    }
    if (data_ != nullptr) {
      ClearInterval(0, size_, data_);
      operator delete(data_);
    }
    data_ = new_data;
    capacity_ = size_;
  }
}

template <class T>
void Vector<T>::ClearInterval(size_t begin, size_t end, T*& data) {
  for (size_t i = begin; i < end; ++i) {
    (data + i)->~ValueType();
  }
}

template <class T>
void Vector<T>::Clear() {
  ClearInterval(0, size_, data_);
  size_ = 0;
}

template <class T>
void Vector<T>::PushBack(const T& value) {
  if (size_ == capacity_) {
    auto new_data = (capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * capacity_ * 2))
                                     : static_cast<T*>(operator new(sizeof(T)));
    size_t i = 0;
    try {
      while (i < size_) {
        new (new_data + i) T(std::move(data_[i]));
        ++i;
      }
    } catch (...) {
      for (size_t j = 0; j < i + 1; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    try {
      new (new_data + size_) T(value);
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    if (data_ != nullptr) {
      ClearInterval(0, size_, data_);
      operator delete(data_);
    }
    data_ = new_data;
    ++size_;
    capacity_ = ((capacity_ != 0) ? 2 * capacity_ : 1);
  } else {
    try {
      new (data_ + size_) T(value);
      ++size_;
    } catch (...) {
      (data_ + size_)->~T();
      throw;
    }
  }
}

template <typename T>
void Vector<T>::PushBack(T&& value) {
  if (size_ == capacity_) {
    auto new_data = (capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * capacity_ * 2))
                                     : static_cast<T*>(operator new(sizeof(T)));
    size_t i = 0;
    try {
      while (i < size_) {
        new (new_data + i) T(std::move(data_[i]));
        ++i;
      }
    } catch (...) {
      for (size_t j = 0; j < i + 1; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    try {
      new (new_data + size_) T(std::move(value));
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        data_[j] = std::move(new_data[j]);
      }
      ClearInterval(0, i + 1, new_data);
      operator delete(new_data);
      throw;
    }
    if (data_ != nullptr) {
      ClearInterval(0, size_, data_);
      operator delete(data_);
    }
    ++size_;
    capacity_ = ((capacity_ != 0) ? 2 * capacity_ : 1);
    data_ = new_data;
  } else {
    try {
      new (data_ + size_) T(std::move(value));
      ++size_;
    } catch (...) {
      (data_ + size_)->~T();
      throw;
    }
  }
}

template <class T>
void Vector<T>::PopBack() {
  if (size_ != 0) {
    (data_ + size_ - 1)->~T();
    --size_;
  }
}

template <class T>
bool operator<(const Vector<T>& left, const Vector<T>& right) {
  for (size_t i = 0; i < std::min(left.size_, right.size_); ++i) {
    if (left[i] != right[i]) {
      return left[i] < right[i];
    }
  }
  return left.size_ < right.size_;
}

template <class T>
bool operator>(const Vector<T>& left, const Vector<T>& right) {
  return right < left;
}

template <class T>
bool operator<=(const Vector<T>& left, const Vector<T>& right) {
  return !(right < left);
}

template <class T>
bool operator>=(const Vector<T>& left, const Vector<T>& right) {
  return !(left < right);
}

template <class T>
bool operator==(const Vector<T>& left, const Vector<T>& right) {
  if (left.size_ != right.size_) {
    return false;
  }
  for (size_t i = 0; i < left.size_; ++i) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}

template <class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right) {
  return !(left == right);
}

#endif