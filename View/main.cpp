//#include <QApplication>
//#include "mainwindow.h"
//
//int main(int argc, char *argv[]) {
//  QLocale::setDefault(QLocale::C);
//  setenv("LC_NUMERIC", "C",1);
//  QApplication a(argc, argv);
//  MainWindow w(nullptr);
//  w.show();
//  return a.exec();
//}

#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Disable the default behavior of the application closing when the last window is closed
    a.setQuitOnLastWindowClosed(false);

    try {
        QLocale::setDefault(QLocale::C);
        setenv("LC_NUMERIC", "C", 1);

        MainWindow w(nullptr);
        w.setWindowTitle("S21 SMART CALC v2.0");
        w.show();

        return a.exec();
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
    }

    return 0;
}
