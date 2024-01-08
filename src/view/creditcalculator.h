/*!
\file
\brief Заголовочный файл creditcalculator.h с реализацией интерфейса кредитного
калькулятора

Данный файл содержит в себе определение класса и его методов
*/
#ifndef CREDITCALCULATOR_H
#define CREDITCALCULATOR_H

#include <QWidget>

#include "../controller/creditcontroller.h"

namespace Ui {
class CreditCalculator;
}

namespace Calc {
class CreditCalculator : public QWidget {
  Q_OBJECT
 public:
  explicit CreditCalculator(QWidget *parent = nullptr);
  ~CreditCalculator();

 private slots:
  void on_clear_clicked();
  void on_button_result_clicked();
  void PrintDataToField(double overpayment, double total);

 private:
  Ui::CreditCalculator *ui;  //< основное окно
};
};      // namespace Calc
#endif  // CREDITCALCULATOR_H
