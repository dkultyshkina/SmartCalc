/*!
\file
\brief Заголовочный файл controller.h с реализацией контроллера паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "../model/model.h"

namespace Calc {
class Controller {
 public:
  Controller();
  Controller(std::string str, double x);
  ~Controller();

  bool GetError() const noexcept;
  double GetValue() const noexcept;

  void ControllerCalculationValue();

 private:
  std::string str_;  //< переменная для хранения уравнения для вычисления
  double value_;  //< переменная для вычисляемого результата
  double x_;  //< переменная для значения x в уравнении
  bool error_;  //< переменная для обозначения для возможной ошибки
};
}  // namespace Calc

#endif  // CONTROLLER_H
