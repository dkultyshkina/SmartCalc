/*!
\file
\brief Заголовочный файл validator.h с реализацией проверки на корректность
строки

Данный файл содержит в себе определение класса Validator и его методов для
реализации проверки на корректность строки
*/
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

namespace Calc {
class Validator {
 public:
  Validator();
  Validator(std::string str);
  ~Validator();

  std::string GetStr() const noexcept;
  bool ValidationOfInputStrings();

 private:
  std::string str_;  //< входная строка с выражением для проверки
  size_t length_;     //< длина строки выражения
  int count_number_;  //< количество чисел в выражении
  int count_backet_;  //< количество скобок в выражении
  int count_point_;   //< количество точек в выражении

  bool IsDigit(size_t *i) const;
  bool IsPoint(size_t *i);
  bool IsOperator(size_t *i) const;
  bool IsX(size_t *i) const;
  bool IsBracketLeft(size_t *i);
  bool IsBracketRight(size_t *i);
  bool CheckUnaryMinus(size_t *i);
  bool CheckBorders(size_t *i) const;
  bool CheckBracket() const;
  bool IsMod(size_t *i);
  bool IsDifficultOperator(size_t *i);
  bool CheckAround(size_t *i) const;
  bool CheckAroundNumber(size_t *i) const;
  bool CheckAroundDifficult(size_t *i) const;
  void CountNumber();
  bool CheckChar(size_t *i);
  bool empty() const;
  bool CheckDifficultOperatorRight(size_t *i) const;
  bool IsExhibotor(size_t *i) const;
  bool CheckExhibotor(size_t *i);
};
};      // namespace Calc
#endif  // VALIDATOR_H
