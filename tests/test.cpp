// Copyright 2020 BoryaBes <box.bern@yandex.ru>
#include <gtest/gtest.h>
#include "stack_task1.hpp"
#include "iostream"
#include "stack_task2.hpp"


TEST(simpleStack, constrWithNoArgument) {//конструктор без аргументов
  Stack<int> stackObj;// создаем объект класса Stack,пустой
  int k = 5;
  int m = 10;
  stackObj.push(k);//добавляем на вершину стека два объекта типа инт
  stackObj.push(m);
  ASSERT_EQ(stackObj.head(), 10);//проверяем, что последний добавленный элемент равен 10
}



TEST(simpleStack, moveable1) {
  ASSERT_EQ(std::is_move_constructible_v<Stack<int>,true);// с 20 по 35 строку идет проверка того, что класс некопируемый но перемещаемый
}


TEST(simpleStack, uncopy) {
  ASSERT_EQ(std::is_copy_constructible_v<Stack<int>,false);
}

TEST(simpleStack, uncopy2) {
  ASSERT_EQ(std::is_copy_assignable_v<Stack<int>,false);
}

TEST(simpleStack, moveable2) {
  ASSERT_EQ(std::is_move_constructible_v<Stack<int>,true);
}

TEST(simpleStack, pushRValue) {// тест проверяет, что мы можем добавлять на вершину стека rvalue значение(которое не проинициализировано)
  Stack<int> stackObj;
  stackObj.push(std::move(8));
  stackObj.push(std::move(4));
  ASSERT_EQ(stackObj.head(), 4);
}

TEST(simpleStack, pushLValue) {// тоже самое только для lvalue( в начале проинициализировали, потом доабавили (k и a это lvalue))
  Stack<int> stackObj;
  int k = 3;
  int a = 18;
  stackObj.push(k);
  stackObj.push(a);
  ASSERT_EQ(stackObj.head(), 18);
}

TEST(simpleStack, pop) {// проверка метода pop(удаление с вершины стека)
  Stack<int> stackObj;
  int k = 3;
  int a = 18;
  stackObj.push(k);
  stackObj.push(a);
  stackObj.pop();
  ASSERT_EQ(stackObj.head(), 3);
}

TEST(simpleStack, popEmpty) {//проверка того, что если стек пустой и мы пытаемся из него удалить элемент выбросится исключение
  Stack<int> stackObj;
  ASSERT_THROW(stackObj.pop(), std::out_of_range);
}

TEST(simpleStack, headEmpty) {//проверка того, что если стек пустой и мы пытаемся узнать значение верхнего элемент выбросится исключение
  Stack<int> stackObj;
  ASSERT_THROW(stackObj.head(), std::out_of_range);
}

TEST(simpleStack, stackExpansion) {// проверка того, что стек расширяет свою емкость по мере необходимости(по дефолту емкость 16 элементов, когда емкости не хватает она автоматически увеличивается в 2 раза)
  Stack<int> stackObj;
  for (int i=0;i<30;++i){
    stackObj.push(std::move(i));
  }
  ASSERT_EQ(stackObj.head(), 29);
}

TEST(hardStack, pushEmplace) {// проверка метода pushEmplace
  HStack<int> stackObj; // передаем в аргумент этому методу неинициализированное выражение, далее этот метод передает его в конструктор типа(у 4 это инт) и конструирует на вершине стека новый объект
  stackObj.push_emplace(4);
  ASSERT_EQ(stackObj.head(), 4);
}

TEST(hardStack, push) {
  HStack<int> stackObj;
  stackObj.push(9);
  ASSERT_EQ(stackObj.head(), 9);
}

TEST(hardStack, pop) {
  HStack<int> stackObj;
  stackObj.push(9);
  stackObj.push(4);
  stackObj.pop();
  ASSERT_EQ(stackObj.head(), 9);
}

TEST(hardStack, headEmpty) {
  HStack<int> stackObj;
  ASSERT_THROW(stackObj.head(), std::out_of_range);
}

TEST(hardStack, popEmptyStack) {
  HStack<int> stackObj;
  ASSERT_THROW(stackObj.pop(), std::out_of_range);
}

TEST(hardStack, stackExpansion) {
  HStack<int> stackObj;
  for (int i=0;i<31;++i){
    stackObj.push(std::move(i));
  }
  ASSERT_EQ(stackObj.head(), 30);
}

TEST(hardStack, constr) {
  HStack<int> stackObj;
  stackObj.push(8);
  HStack<int> stack = HStack(std::move(stackObj));
  ASSERT_EQ(stack.head(), 8);
}
TEST(hardStack, moveable1) {
  ASSERT_EQ(std::is_move_constructible_v<HStack<int>,true);
}


TEST(hardStack, uncopy) {
  ASSERT_EQ(std::is_copy_constructible_v<HStack<int>,false);
}

TEST(hardStack, uncopy2) {
  ASSERT_EQ(std::is_copy_assignable_v<HStack<int>,false);
}

TEST(hardStack, moveable2) {
  ASSERT_EQ(std::is_move_constructible_v<HStack<int>,true);
}