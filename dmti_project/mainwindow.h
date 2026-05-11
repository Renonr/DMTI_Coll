#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QList>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Вперед объявление структур
struct RationalNumber;
struct PolynomialNumber;

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

private:
    void clearFields();
    void createFields(const QStringList &labels, const QString &type);
    QString executeOperation(const QString &type, const QString &func, const QStringList &inputs);
    void saveResultToFile(const QString &type, const QString &func, const QStringList &inputs, const QString &result);
    RationalNumber parseRational(const QString &s);
    PolynomialNumber parsePolynomial(const QString &s);
    PolynomialNumber parsePolynomialExpr(const QString &expr);

    Ui::MainWindow *ui;
    QFormLayout *dynamicLayout = nullptr;
    QList<QLineEdit*> fieldEditors;
};

#endif // MAINWINDOW_H
