#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QList>
#include <QTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QDebug>

#include "logic/natural.h"
#include "logic/integer.h"
#include "logic/rational.h"
#include "logic/polinomial.h"
#include "logic/number_structures.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTypeChanged(int index);
    void onFunctionChanged(int index);
    void onCalculate();
    void onSaveToFile();

private:
    void clearFields();
    void createFields(const QStringList &labels, const QString &type);
    RationalNumber parseRational(const QString &s);
    PolynomialNumber parsePolynomial(const QString &s);
    QString executeOperation(const QString &type, const QString &func, const QStringList &inputs);

    Ui::MainWindow *ui;
    QFormLayout *dynamicLayout;
    QList<QLineEdit*> fieldEditors;

    QTextEdit *resultDisplay;
    QPushButton *saveButton;
    QString lastResult;
};

#endif // MAINWINDOW_H
