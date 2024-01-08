/*!
\file
\brief Исходный файл model.cc с методами класса Model, которые используются при
реализации логики работы программы SmartCalc

Данный файл содержит в себе описание методов класса Model, которые используются
при реализации логики работы проекта SmartCalc
*/

#include "model.h"

namespace Calc {
/*!
Конструктор по умолчанию
*/
Model::Model() : value_(0), x_(0), str_(" "), validator_(" "), error_(false){};
;

/*!
Параметризованный конструктор
\param[in] str переменная, которая содержит в себе уравнение или выражение для
вычисления
*/
Model::Model(std::string str)
    : value_(0), x_(0), str_(str), validator_(str), error_(false){};

/*!
Второй параметризованный конструктор
\param[in] str переменная, которая содержит в себе уравнение или выражение для
вычисления \param[in] x переменная, которая содержит в себе значение для
переменной x
*/
Model::Model(std::string str, double x)
    : value_(0), x_(x), str_(str), validator_(str), error_(false){};

/*!
Деструктор
*/
Model::~Model() = default;

/*!
Возвращает значение приватного поля ошибки
\return значение ошибки true или false
*/
bool Model::GetError() const noexcept { return error_; }

/*!
Возвращает значение приватного поля вычисляемого значения
\return переменная, которая содержит в себе вычисляемое значение
*/
double Model::GetValue() const noexcept { return value_; };

/*!
Проверяет выражение на корректность ввода
*/
void Model::ValidationOfInputString() {
  error_ = validator_.ValidationOfInputStrings();
  str_ = validator_.GetStr();
};

/*!
Вычисляет значение выражения
*/
void Model::СalculateTheFinalValue() {
  if (error_ == true) {
    Calc::Parser parser_(str_);
    parser_.ParserStrToStack();
    std::stack<double> value = parser_.GetStackValue();
    std::stack<int> priority = parser_.GetStackPriority();
    std::stack<int> type = parser_.GetStackType();
    Calc::Notation notation(value, priority, type);
    notation.CalculationNotation();
    value = notation.GetStackValue();
    priority = notation.GetStackPriority();
    type = notation.GetStackType();
    Calc::Calculation calc(value, priority, type, x_);
    calc.CalculationValue();
    if (calc.GetError() == true) {
      error_ = true;
      value_ = 0;
      return;
    }
    value_ = calc.GetValue();
    error_ = false;
  } else {
    error_ = true;
    value_ = 0;
  }
}
};  // namespace Calc
