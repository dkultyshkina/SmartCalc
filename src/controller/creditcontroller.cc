/*!
\file
\brief Исходный файл creditcontroller.cc с методами класса CreditController,
которые используются при реализации контроллера кредитного калькулятора
программы SmartCalc

Данный файл содержит в себе описание методов класса CreditController, которые
используются при реализации контроллера кредитного калькулятора проекта
SmartCalc
*/
#include "creditcontroller.h"

namespace Calc {
/*!
Конструктор по умолчанию
*/
CreditController::CreditController()
    : credit_(), P_(0), overpayment_(0), total_(0), start_(0), end_(0){};

/*!
Параметризованный конструктор
\param[out] P Eжемесячный платеж
\param[out] S Сумма кредита
\param[out] N Срок кредита
\param[out] R Процентная ставка
*/
CreditController::CreditController(double S, int N, double R)
    : credit_(S, N, R), P_(0), overpayment_(0), total_(0), start_(0), end_(0){};

/*!
Деструктор
*/
CreditController::~CreditController() = default;

/*!
Возвращает значение приватного поля переплата по кредиту
\return перемнная, которая содержит в себе переплату по кредиту
*/
double CreditController::GetOverpayment() const noexcept {
  return overpayment_;
};

/*!
Возвращает значение приватного поля общей выплаты
\return перемнная, которая содержит в себе общей выплаты
*/
double CreditController::GetTotal() const noexcept { return total_; };

/*!
Возвращает значение приватного поля выплаты в первом месяце
\return перемнная, которая содержит в себе значение выплаты в первом месяце
*/
double CreditController::GetStart() const noexcept { return start_; };

/*!
Возвращает значение приватного поля выплаты в последнем месяце
\return перемнная, которая содержит в себе значение выплаты в последнем месяце
*/
double CreditController::GetEnd() const noexcept { return end_; };

/*!
Возвращает значение приватного поля ежемесячного платежа
\return перемнная, которая содержит в себе значение ежемесячного платежа
*/
double CreditController::GetP() const noexcept { return P_; };

/*!
Подсчёт кредита по аннуитетному платежу
*/
void CreditController::ControllerCreditCalculatorAnnuity() {
  credit_.CalculationAnnuity();
  overpayment_ = credit_.GetOverpayment();
  P_ = credit_.GetP();
  total_ = credit_.GetTotal();
}

/*!
Подсчёт кредита по дифференцированному платежу
*/
void CreditController::ControllerCreditCalculatorDifferentiated() {
  credit_.СalculationDifferentiated();
  overpayment_ = credit_.GetOverpayment();
  total_ = credit_.GetTotal();
  start_ = credit_.GetStart();
  end_ = credit_.GetEnd();
}

};  // namespace Calc
