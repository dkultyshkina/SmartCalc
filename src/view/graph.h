/*!
\file
\brief Заголовочный файл graph.h с реализацией построения графика заданного
выражения

Данный файл содержит в себе определение класса и его методов
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "../controller/controller.h"

namespace Ui {
class Graph;
}

namespace Calc {
class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 public slots:
  void slot(QString str, QString left, QString right, QString up, QString down);

 private:
  Ui::Graph *ui;              //< основное окно
  double xBegin, xEnd, h, X;  //< начало, конец, шаг, итератор
  int N;                      //<  количество
  QVector<double> x, y;  //< векторы x, y для значений осей графика
};
};      // namespace Calc
#endif  // GRAPH_H
