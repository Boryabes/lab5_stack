// Copyright 2020 BoryaBes <box.bern@yandex.ru>
#include "cstring"
#include "iostream"
template <typename T>
class HStack {
 public:
  HStack() : stack_p(new T[16]), stack_head(0), stack_size(16) {}
  HStack(HStack&& stack){
    stack_head = stack.stack_head;
    stack_p = stack.stack_p;
    stack_size = stack.stack_size;
    stack.m_memp = nullptr;
  };
  template <typename... Args>
  void push_emplace(Args&&... value) { //пушэнплэйс инициализируем объекст на вершине стэка
    if (stack_head == stack_size) {  //передает аргумент в конструктор тип аргумента(передаю 5 он передает в конструктор типа инт)
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
    stack_p[stack_head] = T(value...); //последний элмент становится равным переменной инициализированной конструктором типа этой переменной
    stack_head += 1;
  }
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
  const T& head() const {
    if (stack_head == 0) {
      throw std::out_of_range{"Stack is empty"};
    }
    return stack_p[stack_head - 1];
  };
  T pop() { //поп возвращает ужаленный элемент
    if (stack_head == 0) {
      throw std::out_of_range{"Empty array"};
    }
    stack_head -= 1;
    return stack_p[stack_head];
  };
  ~HStack() { delete[] stack_p; }

 private:
  T* stack_p;        // start
  int stack_head;       // index peak of stack
  int stack_size;  //
};