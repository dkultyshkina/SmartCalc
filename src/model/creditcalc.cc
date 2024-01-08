/*!
\file
\brief Исходный файл creditcalc.cc с методами класса CreditCalc, которые
используются при реализации логики работы кредитного калькулятора

Данный файл содержит в себе описание методов класса CreditCalc, которые
используются при реализации логики работы кредитного калькулятора
*/
#include "creditcalc.h"

namespace Calc {

/*!
Конструктор по умолчанию
*/
CreditCalc::CreditCalc()
    : P_(0),
      S_(0),
      N_(0),
      R_(0),
      overpayment_(0),
      total_(0),
      start_(0),
      end_(0){};

/*!
Параметризованный конструктор
\param[out] P Eжемесячный платеж
\param[out] S Сумма кредита
\param[out] N Срок кредита
\param[out] R Процентная ставка
*/
CreditCalc::CreditCalc(double S, int N, double R)
    : P_(0),
      S_(S),
      N_(N),
      R_(R),
      overpayment_(0),
      total_(0),
      start_(0),
      end_(0){};

/*!
Деструктор
*/
CreditCalc::~CreditCalc() = default;

/*!
Возвращает значение приватного поля переплата по кредиту
\return переменная, которая содержит в себе переплату по кредиту
*/
double CreditCalc::GetOverpayment() const noexcept { return overpayment_; };

/*!
Возвращает значение приватного поля общей выплаты
\return переменная, которая содержит в себе общей выплаты
*/
double CreditCalc::GetTotal() const noexcept { return total_; };

/*!
Возвращает значение приватного поля выплаты в первом месяце
\return переменная, которая содержит в себе значение выплаты в первом месяце
*/
double CreditCalc::GetStart() const noexcept { return start_; };

/*!
Возвращает значение приватного поля выплаты в последнем месяце
\return переменная, которая содержит в себе значение выплаты в последнем месяце
*/
double CreditCalc::GetEnd() const noexcept { return end_; };

/*!
Возвращает значение приватного поля ежемесячного платежа
\return переменная, которая содержит в себе значение ежемесячного платежа
*/
double CreditCalc::GetP() const noexcept { return P_; };

/*!
Подсчёт по формуле для кредитного калькулятора по аннуитетному платежу
*/
void CreditCalc::CalculationAnnuity() {
  P_ = S_ * ((R_ / 12 / 100 * pow(1 + (R_) / 12 / 100, N_)) /
             (pow(1 + (R_) / 12 / 100, N_) - 1));
  total_ = P_ * N_;
  overpayment_ = total_ - S_;
};

/*!
Подсчёт по формуле для кредитного калькулятора по дифференцированному платежу
*/
void CreditCalc::СalculationDifferentiated() {
  for (int i = 1; i <= N_; i++) {
    double PO = S_ / N_;
    P_ = PO + (S_ - PO * (i - 1)) * (R_ / 100 / 12);
    total_ = total_ + (P_);
    if (i == 1) {
      start_ = P_;
    }
    if (i == N_) {
      end_ = P_;
    }
  }
  overpayment_ = total_ - S_;
};

};  // namespace Calc
