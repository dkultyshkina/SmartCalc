/*!
\file
\brief Заголовочный файл creditcalc.h с реализацией модели кредитного
калькулятора паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/
#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <math.h>

namespace Calc {
class CreditCalc {
 public:
  CreditCalc();
  CreditCalc(double S, int N, double R);
  ~CreditCalc();

  double GetOverpayment() const noexcept;
  double GetTotal() const noexcept;
  double GetStart() const noexcept;
  double GetEnd() const noexcept;
  double GetP() const noexcept;

  void CalculationAnnuity();
  void СalculationDifferentiated();

 private:
  double P_;            //< eжемесячный платеж
  double S_;            //< Сумма кредита
  int N_;               //< Срок кредита
  double R_;            //< Процентная ставка
  double overpayment_;  //< Переплата по кредиту
  double total_;        //< Общая выплата
  double start_;        //< Выплата в первом месяце
  double end_;          //< Выплата в последнем месяце
};
};      // namespace Calc
#endif  // CREDITCALC_H
