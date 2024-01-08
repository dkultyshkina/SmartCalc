/*!
\file
\brief Заголовочный файл parser.h с реализацией парсера строки в стек

Данный файл содержит в себе определение класса Parser и его методов для
реализации парсера строки в стек значения, типа и приоритета
*/

#ifndef PARSER_H
#define PARSER_H

#include <math.h>

#include <stack>
#include <string>

namespace Calc {

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

class Parser {
 public:
  Parser();
  Parser(std::string str);
  ~Parser();

  std::stack<double> GetStackValue() const noexcept;
  std::stack<int> GetStackPriority() const noexcept;
  std::stack<int> GetStackType() const noexcept;

  void ParserStrToStack();

 private:
  std::string str_;  //< входная строка с выражением для парсинга
  size_t length_;  //< длина строки выражения
  std::stack<double> stack_value_;  //< стек со значениями
  std::stack<int> stack_priority_;  //< стек с приоритетами
  std::stack<int> stack_type_;      //< стек с типами

  bool IsDigit(size_t *i) const;
  void CheckAndPushDoubleNumber(size_t *i);
  void CheckAndPushX(size_t *i);
  void CheckAndPushOperator(size_t *i);
  bool CheckBorders(size_t *i) const;
  void CheckAndPushDifficultOperator(size_t *i);
  void PushDifficultOperator(std::string &diff_operator, size_t *i);
  void ReverseStacks();
};
};      // namespace Calc
#endif  // PARSER_H
