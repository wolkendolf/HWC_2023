#include <cstring>
#include <iostream>

template <typename T>
struct Node {
  Node* prev;
  Node* next;
  T data;

  explicit Node(T data) : prev(nullptr), next(nullptr), data(data) {
  }
};

template <typename T>
class Deque {
 private:
  Node<T>* head_;
  Node<T>* tail_;
  int size_ = 0;

 public:
  explicit Deque() : head_(nullptr), tail_(nullptr) {
  }
  ~Deque() {
    Clear();
    delete head_;
    delete tail_;
  }

  void PushFront(T elem) {
    auto node = new Node(elem);
    node->next = head_;
    if (head_ != nullptr) {
      head_->prev = node;
    }
    if (tail_ == nullptr) {
      tail_ = node;
    }
    head_ = node;
    ++size_;
    std::cout << "ok\n";
  }

  void PushBack(T elem) {
    auto node = new Node(elem);
    node->prev = tail_;
    if (tail_ != nullptr) {
      tail_->next = node;
    }
    if (head_ == nullptr) {
      head_ = node;
    }
    tail_ = node;
    ++size_;
    std::cout << "ok\n";
  }

  void PopFront() {
    std::cout << head_->data << '\n';
    auto temp = head_->next;
    if (temp != nullptr) {
      temp->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete head_;
    --size_;
    head_ = temp;
  }

  void PopBack() {
    std::cout << tail_->data << '\n';
    auto temp = tail_->prev;
    if (temp != nullptr) {
      temp->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete tail_;
    --size_;
    tail_ = temp;
  }

  void Front() {
    std::cout << head_->data << '\n';
  }

  void Back() {
    std::cout << tail_->data << '\n';
  }

  int Size() {
    return size_;
  }

  void Clear() {
    while (head_ != nullptr) {
      auto temp = head_->next;
      if (temp != nullptr) {
        temp->prev = nullptr;
      } else {
        tail_ = nullptr;
      }
      delete head_;
      head_ = temp;
      --size_;
    }
  }

  void Exit() {
    Clear();
    std::cout << "bye\n";
  }
};

int main() {
  int call_counter = 0;
  std::cin >> call_counter;
  Deque<int> deq;
  char temp[15];
  for (int i = 0; i < call_counter; ++i) {
    std::cin >> temp;
    if (std::strcmp("push_front", temp) == 0) {
      int numb = 0;
      std::cin >> numb;
      deq.PushFront(numb);
      continue;
    }
    if (std::strcmp("push_back", temp) == 0) {
      int numb = 0;
      std::cin >> numb;
      deq.PushBack(numb);
      continue;
    }
    if (std::strcmp("pop_front", temp) == 0) {
      if (deq.Size() == 0) {
        std::cout << "error\n";
      } else {
        deq.PopFront();
        continue;
      }
    }
    if (std::strcmp("pop_back", temp) == 0) {
      if (deq.Size() == 0) {
        std::cout << "error\n";
      } else {
        deq.PopBack();
        continue;
      }
    }
    if (std::strcmp("front", temp) == 0) {
      if (deq.Size() == 0) {
        std::cout << "error\n";
      } else {
        deq.Front();
        continue;
      }
    }
    if (std::strcmp("back", temp) == 0) {
      if (deq.Size() == 0) {
        std::cout << "error\n";
      } else {
        deq.Back();
        continue;
      }
    }
    if (std::strcmp("size", temp) == 0) {
      std::cout << deq.Size() << '\n';
      continue;
    }
    if (std::strcmp("clear", temp) == 0) {
      deq.Clear();
      std::cout << "ok\n";
      continue;
    }
    if (std::strcmp("exit", temp) == 0) {
      deq.Exit();
      return 0;
    }
  }
  deq.Clear();
  return 0;
}