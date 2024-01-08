/*!
\file
\brief Заголовочный файл view.h с реализацией уровня представления паттерна MVC

Данный файл содержит в себе определение класса и его методов
*/
#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <string>

#include "../controller/controller.h"
#include "creditcalculator.h"
#include "depositcalculator.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace Calc {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private:
  Ui::View *ui;        //< основное окно приложения
  Graph *GraphWindow;  //< окно графика
  CreditCalculator *CreditWindow;  //< окно кредитного калькулятора
  DepositCalculator *DepositWindow;  //< окно депозитного калькулятора
  QString
      str_;  //< Переменная, которая содержит в себе данные о строки выражения
  bool error_;  //< Переменная, которая содержит в себе данные об ошибках

 signals:
  void signal(QString str, QString left, QString right, QString up,
              QString down);
 private slots:
  void Digits();
  void ConnectNumbers();
  void ConnectOperation();
  void ChangeStr();
  void on_button_result_clicked();
  void on_button_function_clicked();
  void on_button_clean_clicked();
  void on_button_credit_clicked();
  void on_button_deposit_clicked();
};
};      // namespace Calc
#endif  // VIEW_H
