QT       += core gui widgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_LFLAGS            += -Wall -Wextra -Werror 

CONFIG += c++17
CONFIG += warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/s21_smart_calc_controller.cpp \
    ../Model/s21_smart_calc_model.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../Controller/s21_smart_calc_controller.h \
    ../Model/s21_smart_calc_model.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
