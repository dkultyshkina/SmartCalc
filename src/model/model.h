/*!
\file
\brief Заголовочный файл model.h с реализацией модели паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/

#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <stack>
#include <string>

#include "calculation.h"
#include "notation.h"
#include "parser.h"
#include "validator.h"

namespace Calc {
class Model {
 public:
  friend class Validator;
  friend class Parser;
  friend class Notation;
  friend class Calculation;
  friend class CreditCalculator;

  Model();
  Model(std::string str);
  Model(std::string str, double x);
  ~Model();

  bool GetError() const noexcept;
  double GetValue() const noexcept;
  void ValidationOfInputString();
  void СalculateTheFinalValue();

 private:
  double value_;  //< переменная для вычисляемого результата
  double x_;  //< переменная для значения x в уравнении
  std::string str_;  //< переменная для хранения уравнения для вычисления
  Validator validator_;  //< объект класса валидатора
  bool error_;  //< переменная для обозначения для возможной ошибки
};
};      // namespace Calc
#endif  // MODEL_H
