#include <cstddef>
#include <cstring>
#include <iostream>

template <class T>
struct NodeStack {
  NodeStack<T>* next = nullptr;
  T value;
};

template <class T>
struct Stack {
  NodeStack<T>* back = nullptr;
  size_t size = 0;
};

template <class T>
void PushBack(Stack<T>& stack, const T& value) {
  ++stack.size;
  // В динамической памяти, тк иначе NodeStack уничтожится при выходе из функции
  auto p_node = new NodeStack<T>{stack.back, value};
  stack.back = p_node;
}

template <class T>
void PopBack(Stack<T>& stack) {
  --stack.size;
  NodeStack<T>* p_node = stack.back;
  stack.back = p_node->next;
  delete p_node;
}

template <class T>
T Back(const Stack<T>& stack) {
  return stack.back->value;
}

template <class T>
void Clear(Stack<T>& stack) {
  stack.size = 0;
  while (stack.back) {
    NodeStack<T>* p_node = stack.back;
    stack.back = p_node->next;
    delete p_node;
  }
}

int main() {
  char sequence[100000];
  Stack<char> stack;
  std::string str;
  std::cin.getline(sequence, 100001);
  int i = 0;
  while (sequence[i]) {
    char temp = sequence[i];
    if (temp == '(' || temp == '[' || temp == '{') {
      PushBack(stack, temp);
    } else if (stack.size == 0) {
      std::cout << "NO\n";
      Clear(stack);
      return 0;
    } else {
      if (temp == ')' && Back(stack) == '(') {
        PopBack(stack);
        // std::cout << PopBack(stack) << '\n';
      } else if (temp == ']' && Back(stack) == '[') {
        PopBack(stack);
        // std::cout << PopBack(stack) << '\n';
      } else if (temp == '}' && Back(stack) == '{') {
        PopBack(stack);
        // std::cout << PopBack(stack) << '\n';
      } else {
        std::cout << "NO\n";
        Clear(stack);
        return 0;
      }
    }

    ++i;
  }

  if (stack.size == 0) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  Clear(stack);
  return 0;
}