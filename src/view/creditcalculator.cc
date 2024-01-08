/*!
\file
\brief Исходный файл creditcalculator.cc с методами класса CreditCalculator,
которые используются для построения интерфейса кредитного калькулятора

Данный файл содержит в себе описание методов класса CreditCalculator, которые
используются для построения интерфейса кредитного калькулятора
*/
#include "creditcalculator.h"

#include "ui_creditcalculator.h"

namespace Calc {

/*!
Параметризованный конструктор
\param[out] parent родитель нового виджета
*/
CreditCalculator::CreditCalculator(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalculator) {
  ui->setupUi(this);
  ui->annuity->setChecked(true);
}

/*!
Деструктор
*/
CreditCalculator::~CreditCalculator() { delete ui; }

/*!
Метод, который отвечает за очистку текстовых окон
*/
void CreditCalculator::on_clear_clicked() {
  ui->enter_overpayment->setText("0");
  ui->enter_monthly_payment->setText("0");
  ui->enter_total_payment->setText("0");
}

/*!
Метод, который отвечает за обработку данных из полей после
нажатия кнопки для получения результата и вывода результата в другие поля
*/
void CreditCalculator::on_button_result_clicked() {
  double S = ui->spinbox_total_amount->value();
  double N = ui->spinbox_period->value();
  double R = ui->spinbox_procent->value();
  Calc::CreditController controller(S, N, R);
  if (S == 0 || N == 0 || R == 0) {
    ui->enter_overpayment->setText("Error!");
    ui->enter_total_payment->setText("Error!");
    ui->enter_monthly_payment->setText("Error!");
    return;
  }
  if (ui->annuity->isChecked()) {
    controller.ControllerCreditCalculatorAnnuity();
    double P = controller.GetP();
    if (P < 0) {
      ui->enter_monthly_payment->setText("Error!");
      return;
    }
    QString number = QString::number(P, 'g', 15);
    ui->enter_monthly_payment->setText(number);
  }
  if (ui->differentiated->isChecked()) {
    controller.ControllerCreditCalculatorDifferentiated();
    double start = controller.GetStart();
    double end = controller.GetEnd();
    if (start < 0 || end < 0) {
      ui->enter_monthly_payment->setText("Error!");
      return;
    }
    ui->enter_monthly_payment->setText("C " + QString::number(start, 'g', 15) +
                                       " до " + QString::number(end, 'g', 15));
  }
  double overpayment = controller.GetOverpayment();
  double total = controller.GetTotal();
  PrintDataToField(overpayment, total);
}

/*!
Вывод и проверка на корректность итоговых данных
*/
void CreditCalculator::PrintDataToField(double overpayment, double total) {
  if (overpayment <= 0 && total <= 0) {
    ui->enter_overpayment->setText("Error!");
    ui->enter_total_payment->setText("Error!");
  } else {
    ui->enter_overpayment->setText(QString::number(overpayment, 'g', 15));
    ui->enter_total_payment->setText(QString::number(total, 'g', 15));
  }
}
}  // namespace Calc
