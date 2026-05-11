#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStringList>
#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include "logic/natural.h"
#include "logic/integer.h"
#include "logic/rational.h"
#include "logic/polinomial.h"
#include "logic/number_structures.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!ui->fieldsContainer) {
        qCritical() << "fieldsContainer not found!";
        return;
    }

    if (ui->fieldsContainer->layout()) {
        delete ui->fieldsContainer->layout();
    }

    dynamicLayout = new QFormLayout(ui->fieldsContainer);
    ui->fieldsContainer->setLayout(dynamicLayout);

    ui->typeComboBox->addItems({"Natural", "Integer", "Rational", "Polynomial"});

    ui->funcComboBox->addItems({"COM_NN_D", "NZER_N_B", "ADD_1N_N", "ADD_NN_N", "SUB_NN_N", "MUL_ND_N", "MUL_Nk_N",
                                "MUL_NN_N", "SUB_NDN_N", "DIV_NN_Dk", "DIV_NN_N", "GCF_NN_N", "LCM_NN_N", "MOD_NN_N"});

    createFields({"A", "B"}, "Natural");

    ui->resultLabel->setText("Выберите функцию");

    connect(ui->typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onTypeChanged);
    connect(ui->funcComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFunctionChanged);
    connect(ui->calcButton, &QPushButton::clicked, this, &MainWindow::onCalculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTypeChanged(int index)
{
    if (!ui || !ui->funcComboBox) return;

    QString type = ui->typeComboBox->itemText(index);
    ui->funcComboBox->clear();

    if (type == "Natural")
        ui->funcComboBox->addItems({"COM_NN_D", "NZER_N_B", "ADD_1N_N", "ADD_NN_N", "SUB_NN_N", "MUL_ND_N", "MUL_Nk_N",
                                    "MUL_NN_N", "SUB_NDN_N", "DIV_NN_Dk", "DIV_NN_N", "GCF_NN_N", "LCM_NN_N", "MOD_NN_N"});
    else if (type == "Integer")
        ui->funcComboBox->addItems({"ABS_Z_N", "POZ_Z_D", "MUL_ZM_Z", "TRANS_N_Z", "TRANS_Z_N", "ADD_ZZ_Z", "SUB_ZZ_Z",
                                    "MUL_ZZ_Z", "DIV_ZZ_Z", "MOD_ZZ_Z"});
    else if (type == "Rational")
        ui->funcComboBox->addItems({"ADD_QQ_Q", "SUB_QQ_Q", "MUL_QQ_Q", "DIV_QQ_Q", "RED_Q_Q", "INT_Q_B", "TRANS_Z_Q",
                                    "TRANS_Q_Z"});
    else if (type == "Polynomial")
        ui->funcComboBox->addItems({"ADD_PP_P", "SUB_PP_P", "MUL_PP_P", "MUL_Pxk_P", "MUL_PQ_P", "DIV_PP_P", "MOD_PP_P",
                                    "GCF_PP_P", "NMR_P_P", "DER_P_P", "DEG_P_N", "LED_P_Q", "FAC_P_Q"});

    ui->resultLabel->setText("Выберите функцию");
}

void MainWindow::onFunctionChanged(int index)
{
    if (!ui || !ui->funcComboBox) return;

    QString func = ui->funcComboBox->itemText(index);
    if (func.isEmpty()) return;

    QString type = ui->typeComboBox->currentText();

    QStringList labels;
    if (func == "ADD_1N_N" || func == "NZER_N_B" || func == "ABS_Z_N" || func == "POZ_Z_D" ||
        func == "RED_Q_Q" || func == "INT_Q_B" || func == "DER_P_P" || func == "DEG_P_N" ||
        func == "LED_P_Q" || func == "FAC_P_Q" || func == "MUL_ZM_Z" || func == "TRANS_N_Z" ||
        func == "TRANS_Z_N" || func == "TRANS_Z_Q" || func == "TRANS_Q_Z" || func == "NMR_P_P") {
        labels = {"A"};
    }
    else if (func == "MUL_ND_N" || func == "MUL_Nk_N" || func == "MUL_PQ_P" || func == "MUL_Pxk_P") {
        labels = {"A", "B (цифра)"};
    }
    else if(func == "SUB_NDN_N" || func == "DIV_NN_Dk"){
        labels = {"A", "B", "C (цифра)"};
    }
    else {
        labels = {"A", "B"};
    }

    createFields(labels, type);
    ui->resultLabel->setText("Введите данные");
}
void MainWindow::onCalculate()
{
    QStringList inputs;
    for (auto *edit : fieldEditors) {
        QString val = edit->text().trimmed();
        if (val.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните все поля");
            return;
        }
        inputs << val;
    }

    try {
        QString result = executeOperation(ui->typeComboBox->currentText(),
                                          ui->funcComboBox->currentText(),
                                          inputs);
        ui->resultLabel->setText(result);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", QString::fromUtf8(e.what()));
        ui->resultLabel->setText("Ошибка вычисления");
    }
}

void MainWindow::clearFields()
{
    if (fieldEditors.isEmpty()) {
        return;
    }

    fieldEditors.clear();

    if (dynamicLayout) {
        while (dynamicLayout->count() > 0) {
            QLayoutItem *item = dynamicLayout->takeAt(0);
            if (item) {
                if (item->widget()) {
                    item->widget()->deleteLater();
                }
                delete item;
            }
        }
    }
}

void MainWindow::createFields(const QStringList &labels, const QString &type)
{
    if (!dynamicLayout) {
        qCritical() << "dynamicLayout is null!";
        return;
    }

    clearFields();

    QRegularExpression rx;
    if (type == "Natural")
        rx.setPattern("^(0|[1-9][0-9]*)$");
    else if (type == "Integer")
        rx.setPattern("^-?(0|[1-9][0-9]*)$");
    else if (type == "Rational")
        rx.setPattern("^-?(0|[1-9][0-9]*)/[1-9][0-9]*$");
    else if (type == "Polynomial")
        rx.setPattern(R"(^(-?(0|[1-9][0-9]*)/[1-9][0-9]*|-?(0|[1-9][0-9]*))(\s+(-?(0|[1-9][0-9]*)/[1-9][0-9]*|-?(0|[1-9][0-9]*)))*$)");

    auto *validator = new QRegularExpressionValidator(rx, this);

    for (const QString &label : labels) {
        auto *edit = new QLineEdit(this);
        edit->setValidator(validator);
        edit->setPlaceholderText(label);
        edit->setMinimumWidth(180);

        dynamicLayout->addRow(label + ":", edit);

        fieldEditors.append(edit);
    }

    qDebug() << "Created" << fieldEditors.size() << "fields for" << type;
}

RationalNumber MainWindow::parseRational(const QString &s)
{
    QStringList parts = s.split('/');
    if (parts.size() == 2) {
        return RationalNumber(parts[0], parts[1]);
    }
    return RationalNumber(s, "1");
}

PolynomialNumber MainWindow::parsePolynomial(const QString &s) {
    QStringList coeffStrs = s.split(' ', Qt::SkipEmptyParts);
    if (coeffStrs.isEmpty()) {
        return PolynomialNumber();
    }

    std::vector<RationalNumber> coeffs;
    for (const QString &c : coeffStrs) {
        coeffs.push_back(parseRational(c));
    }

    PolynomialNumber result;
    result.degree = static_cast<int>(coeffs.size()) - 1;
    result.coefficients = coeffs;

    return result;
}

// ==================== ОСНОВНАЯ ЛОГИКА ====================

QString MainWindow::executeOperation(const QString &type, const QString &func, const QStringList &inputs)
{
    // ==================== NATURAL ====================
    if (type == "Natural") {
        if (func == "ADD_1N_N") {
            Number num(inputs[0]);
            return Natural().ADD_1N_N(num).toString();
        }
        else if (func == "ADD_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().ADD_NN_N(a, b).toString();
        }
        else if (func == "SUB_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().SUB_NN_N(a, b).toString();
        }
        else if (func == "MUL_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().MUL_NN_N(a, b).toString();
        }
        else if (func == "DIV_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().DIV_NN_N(a, b).toString();
        }
        else if (func == "MOD_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().MOD_NN_N(a, b).toString();
        }
        else if (func == "GCF_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().GCF_NN_N(a, b).toString();
        }
        else if (func == "LCM_NN_N") {
            Number a(inputs[0]), b(inputs[1]);
            return Natural().LCM_NN_N(a, b).toString();
        }
        else if (func == "COM_NN_D") {
            Number a(inputs[0]), b(inputs[1]);
            return QString::number(Natural().COM_NN_D(a, b));
        }
        else if (func == "NZER_N_B") {
            Number a(inputs[0]);
            return Natural().NZER_N_B(a) ? "true" : "false";
        }
        else if (func == "MUL_ND_N") {
            Number a(inputs[0]);
            int digit = inputs[1].toInt();
            return Natural().MUL_ND_N(a, digit).toString();
        }
        else if (func == "MUL_Nk_N") {
            Number a(inputs[0]);
            int k = inputs[1].toInt();
            return Natural().MUL_Nk_N(a, k).toString();
        }
        else if (func == "SUB_NDN_N") {
            Number a(inputs[0]), b(inputs[1]);
            int digit = inputs[2].toInt();
            return Natural().SUB_NDN_N(a, b, digit).toString();
        }
        else if (func == "DIV_NN_Dk") {
            Number a(inputs[0]);
            Number b(inputs[1]);
            int k = inputs[2].toInt();
            return Natural().DIV_NN_Dk(a, b, k).toString();
        }
    }

    // ==================== INTEGER ====================
    else if (type == "Integer") {
        if (func == "ADD_ZZ_Z") {
            IntegerNumber a(inputs[0]), b(inputs[1]);
            return Integer().ADD_ZZ_Z(a, b).toString();
        }
        else if (func == "SUB_ZZ_Z") {
            IntegerNumber a(inputs[0]), b(inputs[1]);
            return Integer().SUB_ZZ_Z(a, b).toString();
        }
        else if (func == "MUL_ZZ_Z") {
            IntegerNumber a(inputs[0]), b(inputs[1]);
            return Integer().MUL_ZZ_Z(a, b).toString();
        }
        else if (func == "DIV_ZZ_Z") {
            IntegerNumber a(inputs[0]), b(inputs[1]);
            return Integer().DIV_ZZ_Z(a, b).toString();
        }
        else if (func == "MOD_ZZ_Z") {
            IntegerNumber a(inputs[0]), b(inputs[1]);
            return Integer().MOD_ZZ_Z(a, b).toString();
        }
        else if (func == "ABS_Z_N") {
            IntegerNumber a(inputs[0]);
            return Integer().ABS_Z_N(a).toString();
        }
        else if (func == "POZ_Z_D") {
            IntegerNumber a(inputs[0]);
            return QString::number(Integer().SGN_Z_D(a));
        }
        else if (func == "MUL_ZM_Z") {
            IntegerNumber a(inputs[0]);
            return Integer().MUL_ZM_Z(a).toString();
        }
        else if (func == "TRANS_N_Z") {
            Number a(inputs[0]);
            return Integer().TRANS_N_Z(a).toString();
        }
        else if (func == "TRANS_Z_N") {
            IntegerNumber a(inputs[0]);
            return Integer().TRANS_Z_N(a).toString();
        }
    }

    // ==================== RATIONAL ====================
    else if (type == "Rational") {
        if (func == "ADD_QQ_Q") {
            RationalNumber a = parseRational(inputs[0]);
            RationalNumber b = parseRational(inputs[1]);
            return Rational().ADD_QQ_Q(a, b).toString();
        }
        else if (func == "SUB_QQ_Q") {
            RationalNumber a = parseRational(inputs[0]);
            RationalNumber b = parseRational(inputs[1]);
            return Rational().SUB_QQ_Q(a, b).toString();
        }
        else if (func == "MUL_QQ_Q") {
            RationalNumber a = parseRational(inputs[0]);
            RationalNumber b = parseRational(inputs[1]);
            return Rational().MUL_QQ_Q(a, b).toString();
        }
        else if (func == "DIV_QQ_Q") {
            RationalNumber a = parseRational(inputs[0]);
            RationalNumber b = parseRational(inputs[1]);
            return Rational().DIV_QQ_Q(a, b).toString();
        }
        else if (func == "RED_Q_Q") {
            RationalNumber a = parseRational(inputs[0]);
            return Rational().RED_Q_Q(a).toString();
        }
        else if (func == "INT_Q_B") {
            RationalNumber a = parseRational(inputs[0]);
            return Rational().INT_Q_B(a) ? "true" : "false";
        }
        else if (func == "TRANS_Z_Q") {
            IntegerNumber a(inputs[0]);
            return Rational().TRANS_Z_Q(a).toString();
        }
        else if (func == "TRANS_Q_Z") {
            RationalNumber a = parseRational(inputs[0]);
            return Rational().TRANS_Q_Z(a).toString();
        }
    }

    // ==================== POLYNOMIAL ====================
    else if (type == "Polynomial") {
        if (func == "ADD_PP_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            PolynomialNumber b = parsePolynomial(inputs[1]);
            return Polinomial().ADD_PP_P(a, b).toString();
        }
        else if (func == "SUB_PP_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            PolynomialNumber b = parsePolynomial(inputs[1]);
            return Polinomial().SUB_PP_P(a, b).toString();
        }
        else if (func == "MUL_PP_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            PolynomialNumber b = parsePolynomial(inputs[1]);
            return Polinomial().MUL_PP_P(a, b).toString();
        }
        else if (func == "DIV_PP_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            PolynomialNumber b = parsePolynomial(inputs[1]);
            return Polinomial().DIV_PP_P(a, b).toString();
        }
        else if (func == "MOD_PP_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            PolynomialNumber b = parsePolynomial(inputs[1]);
            return Polinomial().MOD_PP_P(a, b).toString();
        }
        else if (func == "GCF_PP_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            PolynomialNumber b = parsePolynomial(inputs[1]);
            return Polinomial().GCF_PP_P(a, b).toString();
        }
        else if (func == "DER_P_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            return Polinomial().DER_P_P(a).toString();
        }
        else if (func == "DEG_P_N") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            return Polinomial().DEG_P_N(a).toString();;
        }
        else if (func == "LED_P_Q") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            return Polinomial().LED_P_Q(a).toString();
        }
        else if (func == "FAC_P_Q") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            return Polinomial().FAC_P_Q(a).toString();
        }
        else if (func == "MUL_PQ_P") {
            PolynomialNumber p = parsePolynomial(inputs[0]);
            RationalNumber q = parseRational(inputs[1]);
            return Polinomial().MUL_PQ_P(p, q).toString();
        }
        else if (func == "MUL_Pxk_P") {
            PolynomialNumber p = parsePolynomial(inputs[0]);
            int k = inputs[1].toInt();
            return Polinomial().MUL_Pxk_P(p, k).toString();
        }
        else if (func == "NMR_P_P") {
            PolynomialNumber a = parsePolynomial(inputs[0]);
            return Polinomial().NMR_P_P(a).toString();
        }
    }

    throw std::runtime_error("Функция не реализована: " + func.toStdString());
}
