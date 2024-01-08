/*!
\file
\brief Заголовочный файл notation.h с реализацией вычисления польской нотации

Данный файл содержит в себе определение класса Notation и его методов для
реализации вычисления польской нотации
*/

#ifndef NOTATION_H
#define NOTATION_H

#include <iostream>
#include <stack>
#include <string>

enum {
  number = 1,  ///< Указывает, что в стеке находится элемент число
  X = 2,  ///< Указывает, что в стеке находится элемент х
  addition = 3,  ///< Указывает, что в стеке находится элемент +
  subtraction = 4,  ///< Указывает, что в стеке находится элемент -
  multiplication = 5,  ///< Указывает, что в стеке находится элемент *
  division = 6,  ///< Указывает, что в стеке находится элемент /
  power = 7,  ///< Указывает, что в стеке находится элемент ^
  modulus = 8,  ///< Указывает, что в стеке находится элемент mod
  cosine = 9,  ///< Указывает, что в стеке находится элемент cos
  sine = 10,  ///< Указывает, что в стеке находится элемент sin
  tangent = 11,  ///< Указывает, что в стеке находится элемент tan
  arccosine = 12,  ///< Указывает, что в стеке находится элемент arccos
  arcsine = 13,  ///< Указывает, что в стеке находится элемент arcsin
  arctangent = 14,  ///< Указывает, что в стеке находится элемент arctan
  squareroot =
      15,  ///< Указывает, что в стеке находится элемент квадратный корень
  naturallogarithm = 16,  ///< Указывает, что в стеке находится элемент ln
  commonlogarithm = 17,  ///< Указывает, что в стеке находится элемент log
  brackets_right = 18,  ///< Указывает, что в стеке находится элемент )
  brackets_left = 19,  ///< Указывает, что в стеке находится элемент (
};

namespace Calc {
class Notation {
 public:
  Notation();
  Notation(std::stack<double> value, std::stack<int> priority,
           std::stack<int> type);
  ~Notation();

  std::stack<double> GetStackValue() const noexcept;
  std::stack<int> GetStackPriority() const noexcept;
  std::stack<int> GetStackType() const noexcept;

  void CalculationNotation();

 private:
  std::stack<double> stack_value_;  //< входной стек со значениями
  std::stack<int> stack_priority_;  //< входной стек с приоритетами
  std::stack<int> stack_type_;  //< входной стек с типами
  std::stack<double> result_stack_value_;  //< стек результата для значений
  std::stack<int> result_stack_priority_;  //< стек результата для приоритетов
  std::stack<int> result_stack_type_;  //< стек результата для типов
  std::stack<double>
      support_stack_value_;  //< вспомогательный стек для значений
  std::stack<int>
      support_stack_priority_;  //< вспомогательный стек для приоритетов
  std::stack<int> support_stack_type_;  //< вспомогательный стек для типов

  void RemainderInSupportStack();

  void CheckTypeForNotation(double& value, int& priority, int& type);

  void HelperForNotation(size_t* i, int* priority_support,
                         double* value_support, int* type_support, int type);

  void PriorityLessOrEqualPrioritySupport(double& value, int& priority,
                                          int& type, double& value_support,
                                          int& priority_support,
                                          int& type_support);

  void TypeNotEqualBracketsRight(int& type, double& value_support,
                                 int& priority_support, int& type_support);

  void CheckPriorityForNotation(double& value, int& priority, int& type);

  void ReverseStacks();
};
};      // namespace Calc
#endif  // NOTATION_H
