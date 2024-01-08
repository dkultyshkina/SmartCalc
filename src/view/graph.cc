/*!
\file
\brief Исходный файл graph.cc с методами класса Graph, которые
используются для построения графика заданного выражения

Данный файл содержит в себе описание методов класса Graph, которые
используются для построения графика заданного выражения
*/
#include "graph.h"

#include "../qt_files/ui_graph.h"

namespace Calc {

/*!
Параметризованный конструктор
\param[out] parent родитель нового виджета
*/
Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

/*!
Деструктор
*/
Graph::~Graph() { delete ui; }

/*!
Слот для отрисовки графика выражения
\param[in] str строка с выражением
\param[in] left левая граница графика
\param[in] right правая граница графика
\param[in] up верхняя граница графика
\param[in] down нижняя граница графика
*/
void Graph::slot(QString str, QString left, QString right, QString up,
                 QString down) {
  ui->widget->clearPlottables();
  if (str.isEmpty()) {
    ui->label->setText("Error!");
    return;
  }
  ui->label->setText(str);
  int left_ = left.toInt(), right_ = right.toInt(), up_ = up.toInt(),
      down_ = down.toInt();
  if (left_ > abs(100000) || right_ > abs(100000) || up_ > abs(100000) ||
      down_ > abs(100000)) {
    h = 100;
  } else if (left_ > abs(10000) || right_ > abs(10000) || up_ > abs(10000) ||
             down_ > abs(10000)) {
    h = 10;
  } else if (left_ > abs(1000) || right_ > abs(1000) || up_ > abs(1000) ||
             down_ > abs(1000)) {
    h = 1;
  } else if (left_ > abs(100) || right_ > abs(100) || up_ > abs(100) ||
             down_ > abs(100)) {
    h = 0.1;
  } else {
    h = 0.01;
  }
  bool error = false;
  double value = 0;
  if (down_ < up_ && left_ < right_) {
    xBegin = left_;
    xEnd = right_;
    ui->widget->xAxis->setRange(left_ - 2, right_ + 2);
    ui->widget->yAxis->setRange(down_ - 2, up_ + 2);
    N = (xEnd - xBegin) / h + 2;
    for (X = xBegin; X <= xEnd; X += h) {
      Calc::Controller controller(str.toStdString(), X);
      controller.ControllerCalculationValue();
      error = controller.GetError();
      if (error == false) {
        x.push_back(X);
        value = controller.GetValue();
        y.push_back(value);
      }
    }
  } else {
    ui->label->setText("Error!");
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}
};  // namespace Calc
