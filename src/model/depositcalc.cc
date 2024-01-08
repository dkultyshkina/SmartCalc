/*!
\file
\brief Исходный файл depositcalc.cc с методами класса DepositCalc, которые
используются при реализации логики работы депозитного калькулятора

Данный файл содержит в себе описание методов класса DepositCalc, которые
используются при реализации логики работы депозитного калькулятора
*/
#include "depositcalc.h"

namespace Calc {
/*!
Конструктор по умолчанию
*/
DepositCalc::DepositCalc()
    : P_(0),
      RE_(0),
      WD_(0),
      N_(0),
      R_(0),
      S_(0),
      total_(0),
      fine_(0),
      index_period_pay_(0),
      index_re_(0),
      index_wd_(0),
      procent_fine_(0){};

/*!
Параметризованный конструктор
\param[in] P Сумма вклада
\param[in] N Срок размещения
\param[in] R Процентная ставка
\param[in] index_period_pay Индекс периодичности выплаты
\param[in] index_re Индекс пополнений
\param[in] index_wd Индекс снятий
\param[in] RE Значение пополнения
\param[in] WD Значение снятий
\param[in]
*/
DepositCalc::DepositCalc(double P, int RE, double WD, int N, double R,
                         int index_period_pay, int index_re, int index_wd,
                         double procent_fine)
    : P_(P),
      RE_(RE),
      WD_(WD),
      N_(N),
      R_(R),
      S_(0),
      total_(0),
      fine_(0),
      index_period_pay_(index_period_pay),
      index_re_(index_re),
      index_wd_(index_wd),
      procent_fine_(procent_fine){};

/*!
Деструктор
*/
DepositCalc::~DepositCalc() = default;

/*!
Возвращает значение приватного поля суммы на вкладе
\return переменная, которая содержит в себе суммы на вкладе
*/
double DepositCalc::GetTotal() const noexcept { return total_; };

/*!
Возвращает значение приватного поля налогов
\return переменная, которая содержит в себе значение налогов
*/
double DepositCalc::GetFine() const noexcept { return fine_; };

/*!
Возвращает значение приватного поля начисленного процента
\return переменная, которая содержит в себе значение начисленного процента
*/
double DepositCalc::GetS() const noexcept { return S_; };

/*!
Подсчёт по формуле для депозитного калькулятора
*/
void DepositCalc::DepositCalculation() {
  int I = 0;
  PeriodForDeposit(&I);
  int wd = 0, re = 0;
  MinusForDeposit(&wd, I);
  PlusForDeposit(&re, I);
  for (int i = 1; i <= I; i++) {
    for (int j = 1; j <= re; j++) {
      P_ = P_ + RE_;
    }
    for (int k = 1; k <= wd; k++) {
      P_ = P_ - WD_;
    }
    S_ = S_ + (P_ * R_ * (N_ / I) / 365) / 100;
  }
  total_ = P_ + S_;
  double max_S = 1000000 * (procent_fine_ / 100);
  if (S_ > max_S) {
    fine_ = (S_ - max_S) * (procent_fine_ / 100);
  }
};

/*!
Подсчёт по формуле для депозитного калькулятора с капитализацией
*/
void DepositCalc::DepositCalculationCapitalization() {
  int I = 0;
  PeriodForDeposit(&I);
  int wd = 0, re = 0;
  MinusForDeposit(&wd, I);
  PlusForDeposit(&re, I);
  for (int i = 1; i <= I; i++) {
    for (int j = 1; j <= re; j++) {
      P_ = P_ + RE_;
    }
    for (int k = 1; k <= wd; k++) {
      P_ = P_ - WD_;
    }
    S_ = S_ + (P_ * R_ * (N_ / I) / 365) / 100;
    P_ = P_ + (P_ * R_ * (N_ / I) / 365) / 100;
  }
  total_ = P_;
  double max_S = 1000000 * (procent_fine_ / 100);
  if (S_ > max_S) {
    fine_ = (S_ - max_S) * (procent_fine_ / 100);
  }
};

/*!
Подсчёт срока периодичности выплаты
\param[out] I Срок периодичности выплаты вклада
*/
void DepositCalc::PeriodForDeposit(int* I) {
  if (index_period_pay_ == 0) {
    *I = N_;
  } else if (index_period_pay_ == 1) {
    *I = ceil(N_ / 7);
  } else if (index_period_pay_ == 2) {
    *I = ceil(N_ / 30.4166666667);
  } else if (index_period_pay_ == 3) {
    *I = ceil(N_ / 30.4166666667 / 3);
  } else if (index_period_pay_ == 4) {
    *I = ceil(N_ / 30.4166666667 / 6);
  } else if (index_period_pay_ == 5) {
    *I = ceil(N_ / 30.4166666667 / 12);
  } else if (index_period_pay_ == 6) {
    *I = 1;
  }
}

/*!
Подсчёт периода снятий вклада
*/
void DepositCalc::MinusForDeposit(int* wd, int& I) {
  if (index_wd_ == 0) {
    *wd = N_;
  } else if (index_wd_ == 1) {
    *wd = ceil(N_ / I / 7);
  } else if (index_wd_ == 2) {
    *wd = ceil(N_ / I / 30.4166666667);
  } else if (index_wd_ == 3) {
    *wd = ceil(N_ / I / 30.4166666667 / 3);
  } else if (index_wd_ == 4) {
    *wd = ceil(N_ / I / 30.4166666667 / 6);
  } else if (index_wd_ == 5) {
    *wd = ceil(N_ / I / 30.4166666667 / 12);
  } else if (index_wd_ == 6) {
    *wd = 1;
  }
}

/*!
Подсчёт периода пополнений вклада
*/
void DepositCalc::PlusForDeposit(int* re, int& I) {
  if (index_re_ == 0) {
    *re = N_;
  } else if (index_re_ == 1) {
    *re = ceil(N_ / I / 7);
  } else if (index_re_ == 2) {
    *re = ceil(N_ / I / 30.4166666667);
  } else if (index_re_ == 3) {
    *re = ceil(N_ / I / 30.4166666667 / 3);
  } else if (index_re_ == 4) {
    *re = ceil(N_ / I / 30.4166666667 / 6);
  } else if (index_re_ == 5) {
    *re = ceil(N_ / I / 30.4166666667 / 12);
  } else if (index_re_ == 6) {
    *re = 1;
  }
}
}  // namespace Calc
