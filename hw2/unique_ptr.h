#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <iostream>

template <typename T>
class UniquePtr {
 private:
  T* ptr_ = nullptr;

 public:
  UniquePtr();
  explicit UniquePtr(T*);
  UniquePtr(UniquePtr&&) noexcept;  // Перемещающий конструктор
  UniquePtr<T>& operator=(UniquePtr&&) noexcept; // Перемещающее присваивание
  ~UniquePtr();

  UniquePtr(const UniquePtr&) = delete; // Конструктор копирования
  UniquePtr<T>& operator=(const UniquePtr<T>*) = delete;  // Копирующее присваивание

  T* Release();
  void Reset(T* ptr = nullptr);
  void Swap(UniquePtr&);
  T* Get() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
};

template <typename T>
UniquePtr<T>::UniquePtr() : ptr_(nullptr) {
}
template <typename T>
UniquePtr<T>::UniquePtr(T* other) : ptr_(other) {
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : ptr_(other.ptr_) {
  other.ptr_ = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
  if (this != &other) {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  return *this;
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
  delete ptr_;
}

template <typename T>
T* UniquePtr<T>::Release() {
  auto temp = ptr_;
  this->ptr_ = nullptr;
  return temp;
}

template <typename T>
void UniquePtr<T>::Reset(T* ptr) {
  if (ptr_ != ptr) {
    delete this->ptr_;
    this->ptr_ = ptr;
  }
}
template <typename T>
void UniquePtr<T>::Swap(UniquePtr& other) {
  auto temp = std::move(*this);
  *this = std::move(other);
  other = std::move(temp);
}

template <typename T>
T* UniquePtr<T>::Get() const {
  return ptr_;
}
template <typename T>
T& UniquePtr<T>::operator*() const {
  return *ptr_;
}
template <typename T>
T* UniquePtr<T>::operator->() const {
  return ptr_;
}
template <typename T>
UniquePtr<T>::operator bool() const {
  return ptr_ != nullptr;
}

#endif
