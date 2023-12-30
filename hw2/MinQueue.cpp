#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>

struct Node {
  int min;
  int value;
  Node() : min(0), value(0) {
  }
  Node(int min, int value) : min(min), value(value) {
  }
};

class MinQueue {
 private:
  size_t len_;  // равно количество запросов к структуре
  size_t size_first_ = 0;
  size_t size_second_ = 0;
  Node* stack_first_;
  Node* stack_second_;

 public:
  explicit MinQueue(size_t len) : len_(len) {
    stack_first_ = new Node[len_];
    stack_second_ = new Node[len_];
  }
  ~MinQueue() {
    delete[] stack_first_;
    delete[] stack_second_;
  }

  void Enqueue(int value) {
    int new_min = size_first_ == 0 ? value : std::min(value, stack_first_[size_first_ - 1].min);
    stack_first_[size_first_] = Node(new_min, value);
    ++size_first_;
    std::cout << "ok\n";
  }

  void Dequeue() {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    if (size_second_ == 0) {
      for (size_t i = size_first_; i != 0; --i) {
        stack_second_[size_second_] = stack_first_[i - 1];
        int n = stack_second_[size_second_].value;  // фиктивная строка для удобочитаемости
        stack_second_[size_second_].min = size_second_ == 0 ? n : std::min(n, stack_second_[size_second_ - 1].min);
        --size_first_;
        ++size_second_;
      }
      std::cout << stack_second_[size_second_ - 1].value << '\n';
      --size_second_;  // удалили головной элемент
    } else {
      std::cout << stack_second_[size_second_ - 1].value << '\n';
      --size_second_;  // удалили головной элемент
    }
  }

  void Front() {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    if (size_second_ == 0) {
      for (size_t i = size_first_; i != 0; --i) {
        stack_second_[size_second_] = stack_first_[i - 1];
        int n = stack_second_[size_second_].value;  // фиктивная строка для удобочитаемости
        stack_second_[size_second_].min = size_second_ == 0 ? n : std::min(n, stack_second_[size_second_ - 1].min);
        --size_first_;
        ++size_second_;
      }
      std::cout << stack_second_[size_second_ - 1].value << '\n';
    } else {
      std::cout << stack_second_[size_second_ - 1].value << '\n';
    }
  }

  size_t Size() {
    return size_first_ + size_second_;
  }

  void Clear() {
    size_first_ = 0;
    size_second_ = 0;
    std::cout << "ok\n";
  }

  void Min() {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    if (size_first_ == 0) {
      std::cout << stack_second_[size_second_ - 1].min << '\n';
    } else if (size_second_ == 0) {
      std::cout << stack_first_[size_first_ - 1].min << '\n';
    } else {
      std::cout << std::min(stack_first_[size_first_ - 1].min, stack_second_[size_second_ - 1].min) << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t len = 0;
  std::cin >> len;

  char command[10];
  MinQueue queue(len);

  for (size_t i = 0; i < len; ++i) {
    std::cin >> command;
    if (std::strcmp("enqueue", command) == 0) {
      int value = 0;
      std::cin >> value;
      queue.Enqueue(value);
    } else if (std::strcmp("dequeue", command) == 0) {
      queue.Dequeue();
    } else if (std::strcmp("front", command) == 0) {
      queue.Front();
    } else if (std::strcmp("size", command) == 0) {
      std::cout << queue.Size() << '\n';
    } else if (std::strcmp("clear", command) == 0) {
      queue.Clear();
    } else if (std::strcmp("min", command) == 0) {
      queue.Min();
    }
  }
}