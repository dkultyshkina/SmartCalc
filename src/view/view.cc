/*!
\file
\brief Исходный файл view.cc с методами класса View, которые
используются при реализации интерфейса программы SmartCalc

Данный файл содержит в себе описание методов класса View, которые
используются при реализации интерфейса проекта SmartCalc
*/

#include "view.h"

#include "../qt_files/ui_view.h"

namespace Calc {

/*!
Параметризованный конструктор
\param[out] parent родитель нового виджета
*/
View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View), str_("") {
  ui->setupUi(this);
  ConnectNumbers();
  ConnectOperation();
  GraphWindow = new Graph;
  CreditWindow = new CreditCalculator;
  DepositWindow = new DepositCalculator;
  connect(this, &View::signal, GraphWindow, &Graph::slot);
}

/*!
Деструктор
*/
View::~View() { delete ui; }

/*!
Слот-обработчик для заполнения основного текстового поля при нажатии кнопок
*/
void View::Digits() {
  ChangeStr();
  QPushButton *button = (QPushButton *)sender();
  QString middle_value = button->text();
  if (middle_value == "sin" || middle_value == "cos" || middle_value == "tan" ||
      middle_value == "acos" || middle_value == "asin" ||
      middle_value == "atan" || middle_value == "sqrt" ||
      middle_value == "ln" || middle_value == "log") {
    middle_value += "(";
  }
  if (ui->lineEdit->displayText().isEmpty() || (str_ == "") ||
      ui->lineEdit->displayText() == "0" ||
      ui->lineEdit->displayText() == "Error!") {
    str_ = "";
    str_ = str_ + middle_value;
  } else {
    str_ = ui->lineEdit->text();
    str_ = str_ + middle_value;
  }
  ui->lineEdit->setText(str_);
}

/*!
Метод, отвечающий за соединение сигналов, слотов и кнопок интерфейса, отвечающих
за цифры
*/
void View::ConnectNumbers() {
  connect(ui->button_zero, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_two, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_three, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_four, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_five, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_six, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_seven, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_eight, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_nine, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_one, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_x, SIGNAL(clicked()), this, SLOT(Digits()));
}

/*!
Метод, отвечающий за соединение сигналов, слотов и кнопок интерфейса, отвечающих
за операции
*/
void View::ConnectOperation() {
  connect(ui->button_multiplication, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_division, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_sum, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_sub, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_degree, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_bracketleft, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_bracketright, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui->button_point, SIGNAL(clicked()), this, SLOT(Digits()));
}

/*!
Метод, отвечающий за изменение переменной str
*/
void View::ChangeStr() {
  if (ui->lineEdit->text() != str_) {
    str_ = ui->lineEdit->text();
  }
}

/*!
Метод, который отвечает за обработку выражения в основном текстовом поле после
нажатия кнопки для получения результата и вывода результата в другое поле
*/
void View::on_button_result_clicked() {
  ChangeStr();
  std::string str = str_.toStdString();
  double x = ui->spinbox_x->value();
  Calc::Controller controller(str, x);
  controller.ControllerCalculationValue();
  error_ = controller.GetError();
  if (error_ == false) {
    double value = controller.GetValue();
    ui->lineEdit->setText(QString::number(value, 'g', 7));
    str_ = "";
  } else {
    ui->lineEdit->setText("Error!");
  }
}

/*!
Метод, который отвечает за вызов окна графика выражения и передачи сигнала этому
окну
*/
void View::on_button_function_clicked() {
  ChangeStr();
  GraphWindow->show();
  emit signal(ui->lineEdit->text(), ui->spinbox_left->text(),
              ui->spinbox_right->text(), ui->spinbox_up->text(),
              ui->spinbox_down->text());
}

/*!
Метод, который отвечает за очистку текстовых окон
*/
void View::on_button_clean_clicked() {
  str_ = "";
  ui->lineEdit->setText("");
}

/*!
Метод, который отвечает за вызов окна кредитного калькулятора
*/
void View::on_button_credit_clicked() { CreditWindow->show(); }

/*!
Метод, который отвечает за вызов окна депозитного калькулятора
*/
void View::on_button_deposit_clicked() { DepositWindow->show(); }

};  // namespace Calc
