/*!
\file
\brief Исходный файл depositcontroller.cc с методами класса DepositController,
которые используются при реализации контроллера депозитного калькулятора
программы SmartCalc

Данный файл содержит в себе описание методов класса DepositController, которые
используются при реализации контроллера депозитного калькулятора проекта
SmartCalc
*/
#include "depositcontroller.h"

namespace Calc {
/*!
Конструктор по умолчанию
*/
DepositController::DepositController()
    : deposit_(), total_(0), S_(0), fine_(0){};

/*!
Параметризованный конструктор
\param[out] P Сумма вклада
\param[out] N Срок размещения
\param[out] R Процентная ставка
\param[out] index_period_pay Индекс периодичности выплаты
\param[out] index_re Индекс пополнений
\param[put] index_wd Индекс снятий
\param[out] RE Значение пополнения
\param[out] WD Значение снятий
\param[out] procent_fine Налоговая ставка
*/
DepositController::DepositController(double P, int RE, double WD, int N,
                                     double R, int index_period_pay,
                                     int index_re, int index_wd,
                                     double procent_fine)
    : deposit_(P, RE, WD, N, R, index_period_pay, index_re, index_wd,
               procent_fine),
      total_(0),
      S_(0),
      fine_(0){};

/*!
Деструктор
*/
DepositController::~DepositController() = default;

/*!
Возвращает значение приватного поля общей выплаты
\return переменная, которая содержит в себе общей выплаты
*/
double DepositController::GetTotal() const noexcept { return total_; };

/*!
Возвращает значение приватного поля налогов
\return переменная, которая содержит в себе значение налогов
*/
double DepositController::GetFine() const noexcept { return fine_; };

/*!
Возвращает значение приватного поля начисленного процента
\return переменная, которая содержит в себе значение начисленного процента
*/
double DepositController::GetS() const noexcept { return S_; };

/*!
Подсчёт по формуле для депозитного калькулятора
*/
void DepositController::ControllerDepositCalculator() {
  deposit_.DepositCalculation();
  S_ = deposit_.GetS();
  total_ = deposit_.GetTotal();
  fine_ = deposit_.GetFine();
};

/*!
Подсчёт по формуле для депозитного калькулятора с капитализацией
*/
void DepositController::ControllerDepositCalculatorCapitalization() {
  deposit_.DepositCalculationCapitalization();
  S_ = deposit_.GetS();
  total_ = deposit_.GetTotal();
  fine_ = deposit_.GetFine();
};

};  // namespace Calc
