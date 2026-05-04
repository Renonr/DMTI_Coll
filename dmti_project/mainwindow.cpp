#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic/number_structures.h"
#include "logic/natural.h"
#include "QRegularExpressionValidator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegularExpression rx("^(0|[1-9][0-9]*)$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);

    ui->lineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text().trimmed().isEmpty()) {
        ui->label->setText("Поле пусто!");
    } else{
        QString data = ui->lineEdit->text();
        Number num = Number(data);
        Number res = Natural().ADD_1N_N(num);
        ui->label->setText(res.toString());
    }
}

