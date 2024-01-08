/*!
\file
\brief Заголовочный файл depositcontroller.h с реализацией контроллера
депозитного калькулятора паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/
#ifndef DEPOSITCONTROLLER_H
#define DEPOSITCONTROLLER_H

#include "../model/depositcalc.h"

namespace Calc {
class DepositController {
 public:
  DepositController();
  DepositController(double P, int RE, double WD, int N, double R,
                    int index_period_pay, int index_re, int index_wd,
                    double procent_fine);
  ~DepositController();

  double GetTotal() const noexcept;
  double GetFine() const noexcept;
  double GetS() const noexcept;

  void ControllerDepositCalculator();
  void ControllerDepositCalculatorCapitalization();

 private:
  DepositCalc deposit_;
  double total_;  //< Общая выплата
  double S_;      //< Начисленные процент
  double fine_;   //< Налоги
};
}  // namespace Calc

#endif  // CONTROLLER_H
