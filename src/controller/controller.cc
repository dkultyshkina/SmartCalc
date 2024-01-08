/*!
\file
\brief Исходный файл controller.cc с методами класса Controller, которые
используются при реализации контроллера программы SmartCalc

Данный файл содержит в себе описание методов класса Controller, которые
используются при реализации контроллера проекта SmartCalc
*/
#include "controller.h"

namespace Calc {
/*!
Конструктор по умолчанию
*/
Controller::Controller() : str_(" "), value_(0), x_(0), error_(false){};

/*!
Параметризованный конструктор
\param[in] str переменная, которая содержит в себе уравнение или выражение для
вычисления \param[in] x переменная, которая содержит в себе значение для
переменной x
*/
Controller::Controller(std::string str, double x)
    : str_(str), value_(0), x_(x), error_(false){};

/*!
Деструктор
*/
Controller::~Controller() = default;

/*!
Возвращает значение приватного поля ошибки
\return значение ошибки true или false
*/
bool Controller::GetError() const noexcept { return error_; }

/*!
Возвращает значение приватного поля вычисляемого значения
\return перемнная, которая содержит в себе вычисляемое значение
*/
double Controller::GetValue() const noexcept { return value_; }

/*!
Подсчёт значения выражения
*/
void Controller::ControllerCalculationValue() {
  Calc::Model model(str_, x_);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  error_ = model.GetError();
  value_ = model.GetValue();
}
};  // namespace Calc
