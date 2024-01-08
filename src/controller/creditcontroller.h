/*!
\file
\brief Заголовочный файл creditcontroller.h с реализацией контроллера кредитного
калькулятора паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/
#ifndef CREDITCONTROLLER_H
#define CREDITCONTROLLER_H

#include "../model/creditcalc.h"

namespace Calc {
class CreditController {
 public:
  CreditController();
  CreditController(double S, int N, double R);
  ~CreditController();

  double GetOverpayment() const noexcept;
  double GetTotal() const noexcept;
  double GetStart() const noexcept;
  double GetEnd() const noexcept;
  double GetP() const noexcept;

  void ControllerCreditCalculatorAnnuity();
  void ControllerCreditCalculatorDifferentiated();

 private:
  CreditCalc credit_;
  double P_;            //< Ежемесячный платеж
  double overpayment_;  //< Переплата по кредиту
  double total_;        //< Общая выплата
  double start_;        //< Выплата в первом месяце
  double end_;          //< Выплата в последнем месяце
};
}  // namespace Calc

#endif  // CREDITCONTROLLER_H
