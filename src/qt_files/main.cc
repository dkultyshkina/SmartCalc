#include <QApplication>

#include "../view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Calc::View w;
  w.show();
  return a.exec();
}
