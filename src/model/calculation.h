/*!
\file
\brief Заголовочный файл calculation.h с реализацией подсчёта результата
выражения

Данный файл содержит в себе определение класса Calculation и его методов для
реализации подсчёта результата выражения с использованием польской нотации
*/

#ifndef CALCULATION_H
#define CALCULATION_H

#include <math.h>

#include <stack>

#include "notation.h"

#define pi_ 3.14

namespace Calc {
class Calculation {
 public:
  Calculation();
  Calculation(std::stack<double> value, std::stack<int> priority,
              std::stack<int> type, double x);
  ~Calculation();

  double GetValue() const noexcept;
  bool GetError() const noexcept;
  void CalculationValue();
  void DifficultOperations(double* first, double* final, int* type);

 private:
  double value_;  //< переменная, которая содержит в себе результат вычисляемого
                  //выражения
  double x_;  //< переменная, которая содержит в себе значение для переменной x
  std::stack<double> stack_value_;  //< стек со входными значениями выражения
  std::stack<int> stack_priority_;  //< входной стек с приоритетами выражения
  std::stack<int> stack_type_;  //< входной стек с типами выражения
  std::stack<double> result_stack_value_;  //< стек для результата значений
  std::stack<int> result_stack_priority_;  //< стек для результата приоритетов
  std::stack<int> result_stack_type_;  //< стек для результата типов
  bool error_;  //< переменная, содержащая значение потенциальной ошибки,
                //возникшей в ходе выполнения

  void ReplaceX(double* value, int* type);
  void PushStack(double* final);
  bool SimpleOperations(double* first, double* second, double* final,
                        int* type);
  void PerformOperations(int* type);
};
};      // namespace Calc
#endif  // CALCULATION_H
