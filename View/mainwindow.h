#include <QMainWindow>
#include <QKeyEvent>


#include "../Controller/s21_smart_calc_controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::SmartCalcController *calc_controller;
  void Append(QString text);
  void Equal();
  void CalculateInput(QString input);
  void BackspaceClicked();
  void ShowGraphic();
  void Clear();
  void keyPressEvent(QKeyEvent *event);
};
