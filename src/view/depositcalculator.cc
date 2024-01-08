/*!
\file
\brief Исходный файл depositcalculator.cc с методами класса DepositCalculator,
которые используются для построения интерфейса депозитного калькулятора

Данный файл содержит в себе описание методов класса DepositCalculator, которые
используются для построения интерфейса депозитного калькулятора
*/
#include "depositcalculator.h"

#include "ui_depositcalculator.h"

namespace Calc {

/*!
Параметризованный конструктор
\param[out] parent родитель нового виджета
*/
DepositCalculator::DepositCalculator(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositCalculator) {
  ui->setupUi(this);
  QDate date = ui->date->date().currentDate();
  QString str = date.toString();
  std::string str_ = str.toStdString();
  ui->date->date().setDate(date.year(), date.month(), date.day());
}

/*!
Деструктор
*/
DepositCalculator::~DepositCalculator() { delete ui; }

/*!
Метод, который отвечает за очистку текстовых окон
*/
void DepositCalculator::on_clear_clicked() {
  ui->enter_fine->setText("0");
  ui->enter_total_sum->setText("0");
  ui->enter_procent->setText("0");
}

/*!
Метод, который отвечает за обработку данных из полей после
нажатия кнопки для получения результата и вывода результата в другие поля
*/
void DepositCalculator::on_result_button_clicked() {
  AssigningValues();
  int N = CountDay();
  if (((index_period_ == 0) &&
       (index_period_pay_ > 1 && (N > 8) && index_period_pay_ != 6)) ||
      (index_period_ == 1 && (((index_period_pay_ == 2 && N < 6) ||
                               (index_period_pay_ == 3 && N < 3) ||
                               (index_period_pay_ == 4 && N < 6) ||
                               (index_period_pay_ == 5 && N < 12)) &&
                              index_period_pay_ != 6)) ||
      ((index_period_ == 0) && (index_re_ > 0 && index_re_ != 6)) ||
      ((index_period_ == 1) &&
       (((index_re_ == 2 && N < 6) || (index_re_ == 3 && N < 3) ||
         (index_re_ == 4 && N < 6) || (index_re_ == 5 && N < 12)) &&
        index_re_ != 6)) ||
      ((index_period_ == 1) &&
       (((index_wd_ == 2 && N < 6) || (index_wd_ == 3 && N < 3) ||
         (index_wd_ == 4 && N < 6) || (index_wd_ == 5 && N < 12)) &&
        index_wd_ != 6)) ||
      ((index_period_ == 0) && (index_re_ > 0 && index_re_ != 6)) || P_ == 0 ||
      N == 0 || R_ == 0) {
    ui->enter_fine->setText("Error!");
    ui->enter_total_sum->setText("Error!");
    ui->enter_procent->setText("Error!");
    return;
  }
  Calc::DepositController controller(P_, re_, wd_, N, R_, index_period_pay_,
                                     index_re_, index_wd_, procent_fine_);
  if (ui->capitalization->isChecked()) {
    controller.ControllerDepositCalculatorCapitalization();
  } else {
    controller.ControllerDepositCalculator();
  }
  double fine = controller.GetFine();
  double total = controller.GetTotal();
  double S = controller.GetS();
  PrintDataToField(fine, total, S);
}

/*!
Метод, отвечающий за чтение из полей интерфейса значений и их присваивание
приватным полям
*/

void DepositCalculator::AssigningValues() {
  P_ = ui->spinbox_amount->value();
  re_ = ui->spinbox_replenishment->value();
  wd_ = ui->spinbox_withdraw->value();
  R_ = ui->spinbox_procent->value();
  procent_fine_ = ui->spinbox_procent_fine->value();
  index_period_ = ui->choice_period->currentIndex();
  index_period_pay_ = ui->comboBox_period_payment->currentIndex();
  index_re_ = ui->choice_replenishment->currentIndex();
  index_wd_ = ui->choice_withdraw->currentIndex();
}

/*!
Подсчёт дней на период вклада
*/
int DepositCalculator::CountDay() {
  int N = ui->spinbox_period->value();
  index_period_ = ui->choice_period->currentIndex();
  QDate new_date;
  qint64 n;
  if (index_period_ == 1) {
    new_date = ui->date->date().addMonths(N);
    n = ui->date->date().daysTo(new_date);
  } else if (index_period_ == 2) {
    new_date = ui->date->date().addYears(N);
    n = ui->date->date().daysTo(new_date);
  } else {
    new_date = ui->date->date().addDays(N);
    n = ui->date->date().daysTo(new_date);
  }
  N = static_cast<int>(n);
  return N;
}

/*!
Вывод и проверка на корректность итоговых данных
*/
void DepositCalculator::PrintDataToField(double fine, double total, double S) {
  if (fine >= 0 && total >= 0 && S >= 0) {
    ui->enter_fine->setText(QString::number(fine, 'g', 7));
    ui->enter_total_sum->setText(QString::number(total, 'g', 7));
    ui->enter_procent->setText(QString::number(S, 'g', 7));
  } else {
    ui->enter_fine->setText("Error!");
    ui->enter_total_sum->setText("Error!");
    ui->enter_procent->setText("Error!");
  }
}
};  // namespace Calc
