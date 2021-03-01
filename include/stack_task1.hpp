// Copyright 2020 BoryaBes <box.bern@yandex.ru>
#include <cstring>
#include <utility>

#include "iostream"
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

template <typename T>
class Stack {
 public:
  Stack() : stack_p(new T[16]), stack_head(0), stack_size(16) {}
  Stack(Stack&& stack) {
    stack_head = stack.m_head;
    stack_p = stack.stack_p;
    stack_size = stack.m_stackSize;
    stack.stack_p = nullptr;
  };
  Stack(const Stack&) = delete;

  void push(T&& value) {
    if (stack_head == stack_size) {
      T* tmp = new T[stack_size * 2];
      if (tmp != nullptr) {
        std::memcpy(tmp, stack_p, stack_size * sizeof(T));
        stack_size = stack_size * 2;
        delete[]stack_p;
        stack_p = tmp;
      } else {
        throw "No memory for element";
      }
    }
    stack_p[stack_head] = std::move(value);
    stack_head += 1;
  };

  void push(const T& value) {
    if (stack_head == stack_size) {
      T* tmp = new T[stack_size * 2];
      if (tmp != nullptr) {
        std::memcpy(tmp, stack_p, stack_size * sizeof(T));
        stack_size = stack_size * 2;
        delete[]stack_p;
        stack_p = tmp;
      } else {
        throw "No memory for element";
      }
    }
    stack_p[stack_head] = value;
    stack_head += 1;
  };
  void pop() {
    if (stack_head == 0) {
      throw std::out_of_range{"Empty stack"};
    }
    stack_head -= 1;
  };
  const T& head() const {
    if (stack_head == 0) {
      throw std::out_of_range{"Stack is empty"};
    }
    return stack_p[stack_head - 1];
  };
  ~Stack() { delete[] stack_p; }

 private:
  T* stack_p;
  int stack_head;
  int stack_size;
};

#endif  // INCLUDE_HEADER_HPP_