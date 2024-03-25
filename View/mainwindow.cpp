#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  s21::SmartCalcModel calc_model;
  calc_controller = new s21::SmartCalcController();

  ui->setupUi(this);

    QPushButton* buttons[] = {
            ui->pushButton_0, ui->pushButton_1, ui->pushButton_2, ui->pushButton_3,
            ui->pushButton_4, ui->pushButton_5, ui->pushButton_6, ui->pushButton_7,
            ui->pushButton_8, ui->pushButton_9
    };

    for (QPushButton* button : buttons) {
        connect(button, &QPushButton::clicked, this, [this, button] {
            Append(button->text());
        });
    }

  connect(ui->pushButton_left_brace, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_left_brace->text()); });
  connect(ui->pushButton_right_brace, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_right_brace->text()); });
  connect(ui->pushButton_pow, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_pow->text()); });
  connect(ui->pushButton_division, &QPushButton::clicked, this,
          [this] { Append("/"); });
  connect(ui->pushButton_multiplication, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_multiplication->text()); });
  connect(ui->pushButton_plus, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_plus->text()); });
  connect(ui->pushButton_minus, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_minus->text()); });
  connect(ui->pushButton_dot, &QPushButton::clicked, this,
          [this] { Append(ui->pushButton_dot->text()); });
  connect(ui->pushButton_mod, &QPushButton::clicked, this,
          [this] { Append("%"); });

  connect(ui->pushButton_sin, &QPushButton::clicked, this,
          [this] { Append("sin("); });
  connect(ui->pushButton_cos, &QPushButton::clicked, this,
          [this] { Append("cos("); });
  connect(ui->pushButton_tan, &QPushButton::clicked, this,
          [this] { Append("tan("); });
  connect(ui->pushButton_sqrt, &QPushButton::clicked, this,
          [this] { Append("sqrt("); });
  connect(ui->pushButton_asin, &QPushButton::clicked, this,
          [this] { Append("asin("); });
  connect(ui->pushButton_acos, &QPushButton::clicked, this,
          [this] { Append("acos("); });
  connect(ui->pushButton_atan, &QPushButton::clicked, this,
          [this] { Append("atan("); });
  connect(ui->pushButton_ln, &QPushButton::clicked, this,
          [this] { Append("ln("); });
  connect(ui->pushButton_log, &QPushButton::clicked, this,
          [this] { Append("log("); });

  connect(ui->pushButton_backspace, &QPushButton::clicked, this,
          &MainWindow::BackspaceClicked);
  connect(ui->pushButton_AC, &QPushButton::clicked, this, &MainWindow::Clear);
  connect(ui->pushButton_x, &QPushButton::clicked, this,
          [this] { Append("x"); });
  connect(ui->pushButton_equal, &QPushButton::clicked, this,
          [this] { Equal(); });
  connect(ui->show_graphic, &QPushButton::clicked, this,
          [this] { ShowGraphic(); });

  ui->customPlot->xAxis->setRange(-10, 10);
  ui->customPlot->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Append(QString text) {
    if (ui->textEdit->toPlainText() == "Incorrect input!" ||
        ui->textEdit->toPlainText() == "The input is too long! Input must be less than 255 symbols" ||
        ui->textEdit->toPlainText() == "0,000000") {
        ui->textEdit->clear();
    }
  if ((text == "+" || text == "-") &&
      (ui->textEdit->toPlainText().endsWith("+") ||
       ui->textEdit->toPlainText().endsWith("-"))) {
    BackspaceClicked();
    ui->textEdit->setText(ui->textEdit->toPlainText() + text);
  } else
      if (text == ".") {
          text = ",";
      }
      ui->textEdit->setText(ui->textEdit->toPlainText() + text);

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        Equal();
    } else if (event->key() == Qt::Key_Backspace) {
        BackspaceClicked();
    } else if (event->key() == Qt::Key_Delete) {
        Clear();
    } else {
        QString text = event->text();
        Append(text);
    }
}

void MainWindow::BackspaceClicked() {
    if (ui->textEdit->toPlainText() == "Incorrect input!" ||
        ui->textEdit->toPlainText() == "The input is too long! Input must be less than 255 symbols" ||
        ui->textEdit->toPlainText() == "0,000000") {
        ui->textEdit->clear();
    }
    ui->textEdit->setText(ui->textEdit->toPlainText().remove(-1, 1));
}

void MainWindow::Equal() {
  QString input = ui->textEdit->toPlainText();
  if (input.contains("x")) {
    int i = 0;
    while (ui->inputX->text().toStdString().c_str()[i]) {
      if (ui->inputX->text().toStdString().c_str()[i] != '.' &&
          ui->inputX->text().toStdString().c_str()[i] != ',' &&
          ui->inputX->text().toStdString().c_str()[i] != '-' &&
          ui->inputX->text().toStdString().c_str()[i] != '+' &&
          (ui->inputX->text().toStdString().c_str()[i] < '0' ||
           ui->inputX->text().toStdString().c_str()[i] > '9')) {
        ui->inputX->setText("Incorrect!");
        break;
      }
      i++;
    }
    if (ui->inputX->text() != "Incorrect!") {
      if (ui->inputX->text() == "") {
        ui->inputX->text() = "0";
      }
      input.replace("x", ui->inputX->text());
      input.replace(".", ",");
        CalculateInput(input);
    }
  } else {
      CalculateInput(input);
  }
}

void MainWindow::CalculateInput(QString input) {
    if (input.length() > 255) {
        ui->textEdit->setText("The input is too long! Input must be less than 255 symbols");
    } else {
        bool status;
        std::string inputString = input.toStdString();
        status = calc_controller->Calculate(inputString);
        if (!status) {
            ui->textEdit->setText("Incorrect input!");
        } else {
            std::string result = calc_controller->GetResult();
            ui->textEdit->setText(QString::fromLocal8Bit(result.c_str()));
        }
    }
}



void MainWindow::ShowGraphic() {
  ui->customPlot->clearGraphs();
  ui->customPlot->legend->setVisible(true);
  ui->customPlot->legend->setFont(QFont("Helvetica", 9));
  ui->customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  ui->customPlot->addGraph();
  QPen pen;
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(3);
  pen.setColor(QColor(220, 138, 221));
  ui->customPlot->graph(0)->setName("Graph");
  ui->customPlot->graph(0)->setPen(pen);
  double x1 = std::stod("-10");
  double x2 = std::stod("10");
  QString formula = ui->textEdit->toPlainText();
  QString temp;
  QVector<double> X, Y;
  double step = (x2 - x1) / 1000;
  for (; x1 <= x2; x1 += step + 0.001) {
    QString s_x1 = QString::number(x1);
    temp = formula;
    formula.replace("x", QString::number(x1));
    formula.replace(".", ",");
    if (formula.length() > 255) {
      ui->textEdit->setText(
          "The input is too long! Input must be less than 255 symbols");
      break;
    } else {
      bool status;
      std::string formulaString = formula.toStdString();
      status = calc_controller->Calculate(formulaString);
      if (!status) {
        ui->textEdit->setText("Incorrect input!");
        break;
      } else {
        if (calc_controller->GetResult() == "nan" ||
            calc_controller->GetResult() == "-nan") {
          formula = temp;
          continue;
        }
        X.push_back(x1);
        Y.push_back(std::stold(calc_controller->GetResult()));
        formula = temp;
        ui->customPlot->graph(0)->addData(X, Y);
        ui->customPlot->xAxis->setRange(-10, 10);
        ui->customPlot->yAxis->setRange(-10, 10);
        ui->customPlot->replot();
      }
    }
  }
  X.clear();
  Y.clear();
}

void MainWindow::Clear() {
  ui->textEdit->setText("");
  ui->inputX->setText("");
  ui->customPlot->clearGraphs();
  ui->customPlot->replot();
}
