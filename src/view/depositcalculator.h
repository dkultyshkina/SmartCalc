/*!
\file
\brief Заголовочный файл depositcalculator.h с реализацией интерфейса
депозитного калькулятора

Данный файл содержит в себе определение класса и его методов
*/
#ifndef DEPOSITCALCULATOR_H
#define DEPOSITCALCULATOR_H

#include <QWidget>

#include "../controller/depositcontroller.h"

namespace Ui {
class DepositCalculator;
}

namespace Calc {
class DepositCalculator : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalculator(QWidget *parent = nullptr);
  ~DepositCalculator();

 private slots:
  void on_clear_clicked();
  void on_result_button_clicked();
  void AssigningValues();
  int CountDay();
  void PrintDataToField(double fine, double total, double S);

 private:
  Ui::DepositCalculator *ui;  //< основное окно
  double P_;
  double re_;
  double wd_;
  double R_;
  double procent_fine_;
  int index_period_;
  int index_period_pay_;
  int index_re_;
  int index_wd_;
};
};      // namespace Calc
#endif  // DEPOSITCALCULATOR_H
