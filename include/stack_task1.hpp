// Copyright 2020 BoryaBes <box.bern@yandex.ru>
#include <cstring>
#include <utility>

#include "iostream"
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

template <typename T>
class Stack {
 public:
  Stack() : stack_p(new T[16]), stack_head(0), stack_size(16) {} //список инициализации, через двоеточие указываю чему равны приватные поля(выделяю дин массив 16 элементов
  Stack(Stack&& stack) { //р вэлью значение принимаем,передаю объекст класса стэк
    stack_head = stack.m_head; //беру поля объекста класса стэк, перемещаю в новый объекст класса стэк
    stack_p = stack.stack_p;
    stack_size = stack.m_stackSize;
    stack.stack_p = nullptr; //обнуляю старый указатель на стэк
  };
  Stack(const Stack&) = delete;  // некопируемый констурктор

  void push(T&& value) { //добавление нового элемента на вершину стэка(принимает эрвэлью
    if (stack_head == stack_size) { //проверяю есть ли 16 уже внутри
      T* tmp = new T[stack_size * 2]; //создаю новый временный массив выделяю дин массив в два раза больше старого
      if (tmp != nullptr) { //если память которую я выделил нулптр
        std::memcpy(tmp, stack_p, stack_size * sizeof(T)); //если не нулптр,из старого массива в котором закончилось место копирую все значения в новый большой массив
        stack_size = stack_size * 2; //значение емкости на два
        delete[]stack_p; //удаляю из памяти старый массив
        stack_p = tmp; //присваиваю старому массиу большой новый
      } else {
        throw "No memory for element"; //если нулптр то память не выделилась
      }
    }
    stack_p[stack_head] = std::move(value); //стекхэд указывает на индекс самого верхнего элмента свободного, и присваиваю вэлью, который мне передал,мув функция которая преобразуют эльвэлью в эрвэлью
    stack_head += 1; //увеличиваем кол-во элементов в стэке на 1
  };

  void push(const T& value) { //тоже самое только для элвэлью
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
  void pop() { //для удаления верхнего элемента стэка
    if (stack_head == 0) { //если стэк пустой то удалять нечего
      throw std::out_of_range{"Empty stack"};
    }
    stack_head -= 1; //если не пустой то уменьшая на единицу размер стэка
  };
  const T& head() const { //возвращает последний элемент
    if (stack_head == 0) { //если пустой то исключение
      throw std::out_of_range{"Stack is empty"};
    }
    return stack_p[stack_head - 1]; //если нет то возвращаю последний элемент стэка
  };
  ~Stack() { delete[] stack_p; } //диструктор, если выходим из области видимости то удаляем из области памяти стэк

 private:
  T* stack_p;        // указатель на первый элемент массива
  int stack_head;       // индекс самого верхнего элемента
  int stack_size;  // емкость стэка
};

#endif  // INCLUDE_HEADER_HPP_