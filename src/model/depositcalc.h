/*!
\file
\brief Заголовочный файл depositcalc.h с реализацией модели депозитного
калькулятора паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/
#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <math.h>

#include <iostream>

namespace Calc {
class DepositCalc {
 public:
  DepositCalc();
  DepositCalc(double P, int RE, double WD, int N, double R,
              int index_period_pay, int index_re, int index_wd,
              double procent_fine);
  ~DepositCalc();

  double GetTotal() const noexcept;
  double GetFine() const noexcept;
  double GetS() const noexcept;

  void DepositCalculation();
  void DepositCalculationCapitalization();

 private:
  double P_;              //< Сумма вклада
  double RE_;             //< Значение пополнения
  double WD_;             //< Значение снятий
  int N_;                 //< Срок размещения
  double R_;              //< Процентная ставка
  double S_;              //< Начисленные проценты
  double total_;          //< Сумма на вкладе
  double fine_;           //< Налоги
  int index_period_pay_;  //< Индекс периодичности выплаты
  int index_re_;          //< Индекс пополнений
  int index_wd_;          //< Индекс снятий
  double procent_fine_;  //< Налоговая ставка

  void PeriodForDeposit(int* I);
  void MinusForDeposit(int* wd, int& I);
  void PlusForDeposit(int* re, int& I);
};
};      // namespace Calc
#endif  // DEPOSITCALC_H
