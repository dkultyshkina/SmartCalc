QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/calculation.cc \
    ../controller/controller.cc \
    ../controller/creditcontroller.cc \
    ../controller/depositcontroller.cc \
    ../view/graph.cc \
    ../view/creditcalculator.cc \
    ../view//depositcalculator.cc \
    main.cc \
    ../model/model.cc \
    ../model/notation.cc \
    ../model/parser.cc \
    qcustomplot.cpp \
    ../model/validator.cc \
    ../view/view.cc \
    ../model/creditcalc.cc \
    ../model/depositcalc.cc

HEADERS += \
    ../model/calculation.h \
    ../controller/controller.h \
    ../controller/creditcontroller.h \
    ../controller/depositcontroller.h \
    ../view/graph.h \
    ../model/model.h \
    ../model/notation.h \
    ../model/parser.h \
    ../view/creditcalculator.h \
    ../view/depositcalculator.h \
    qcustomplot.h \
    ../model/validator.h \
    ../view/view.h \
    ../model/creditcalc.h \
    ../model/depositcalc.h

FORMS += \
    ../view/graph.ui \
    ../view/graph.ui \
    ../view/view.ui \
    ../view/creditcalculator.ui \
    ../view/depositcalculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
