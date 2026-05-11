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
#include <QTextEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QDateTime>

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
    setWindowTitle("Калькулятор");
    setMinimumSize(800, 600);

    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    auto *inputScroll = new QScrollArea(this);
    inputScroll->setWidgetResizable(true);
    inputScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    inputScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    inputScroll->setMaximumHeight(250);

    auto *inputContainer = new QWidget(inputScroll);
    ui->fieldsContainer = inputContainer;

    dynamicLayout = new QFormLayout(inputContainer);
    dynamicLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    dynamicLayout->setLabelAlignment(Qt::AlignRight);
    inputContainer->setLayout(dynamicLayout);
    inputScroll->setWidget(inputContainer);

    auto *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(new QLabel("Тип:", this));
    ui->typeComboBox = new QComboBox(this);
    ui->typeComboBox->addItems({"Natural", "Integer", "Rational", "Polynomial"});
    ui->typeComboBox->setMinimumWidth(120);
    controlsLayout->addWidget(ui->typeComboBox);

    controlsLayout->addWidget(new QLabel("Функция:", this));
    ui->funcComboBox = new QComboBox(this);
    ui->funcComboBox->addItems({"COM_NN_D", "NZER_N_B", "ADD_1N_N", "ADD_NN_N", "SUB_NN_N", "MUL_ND_N", "MUL_Nk_N",
                                "MUL_NN_N", "SUB_NDN_N", "DIV_NN_Dk", "DIV_NN_N", "GCF_NN_N", "LCM_NN_N", "MOD_NN_N"});
    ui->funcComboBox->setMinimumWidth(200);
    controlsLayout->addWidget(ui->funcComboBox);
    controlsLayout->addStretch();

    auto *actionLayout = new QHBoxLayout();
    ui->calcButton = new QPushButton("Рассчитать", this);
    ui->calcButton->setMinimumWidth(100);
    actionLayout->addWidget(ui->calcButton);

    saveButton = new QPushButton("💾 Сохранить результат", this);
    saveButton->setMinimumWidth(150);
    saveButton->setEnabled(false);  // ✅ Неактивна, пока нет результата
    saveButton->setToolTip("Сохранить результат в текстовый файл");
    actionLayout->addWidget(saveButton);
    actionLayout->addStretch();

    resultDisplay = new QTextEdit(this);
    resultDisplay->setReadOnly(true);
    resultDisplay->setPlaceholderText("Результат появится здесь...");
    resultDisplay->setMinimumHeight(80);
    resultDisplay->setMaximumHeight(200);
    resultDisplay->setLineWrapMode(QTextEdit::WidgetWidth);
    resultDisplay->setFont(QFont("Consolas", 10));  // ✅ Моноширинный шрифт
    resultDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    resultDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(inputScroll);
    mainLayout->addLayout(actionLayout);
    mainLayout->addWidget(new QLabel("Результат:", this));
    mainLayout->addWidget(resultDisplay);
    mainLayout->addStretch();

    setCentralWidget(centralWidget);

    createFields({"A", "B"}, "Natural");
    resultDisplay->setText("Выберите функцию и введите данные");

    connect(ui->typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onTypeChanged);
    connect(ui->funcComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFunctionChanged);
    connect(ui->calcButton, &QPushButton::clicked, this, &MainWindow::onCalculate);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveToFile);  // ✅ Новая кнопка
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

    resultDisplay->setText("Выберите функцию");
    saveButton->setEnabled(false);
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
    resultDisplay->setText("Введите данные");
    saveButton->setEnabled(false);
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

    QString type = ui->typeComboBox->currentText();
    QString func = ui->funcComboBox->currentText();

    try {
        QString result = executeOperation(ui->typeComboBox->currentText(),
                                          ui->funcComboBox->currentText(),
                                          inputs);

        if (result.length() > 100) {
            QString formatted;
            int pos = 0;
            while (pos < result.length()) {
                int nextSpace = result.indexOf(' ', pos + 80);
                if (nextSpace == -1) nextSpace = result.length();
                formatted += result.mid(pos, nextSpace - pos) + "\n";
                pos = nextSpace + 1;
            }
            result = formatted.trimmed();
        }

        resultDisplay->setText(result);
        lastResult = result;
        saveButton->setEnabled(true);

        // Прокрутка в начало
        QTextCursor cursor = resultDisplay->textCursor();
        cursor.setPosition(0);
        resultDisplay->setTextCursor(cursor);
        resultDisplay->ensureCursorVisible();

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", QString::fromUtf8(e.what()));
        resultDisplay->setText("Ошибка: " + QString::fromUtf8(e.what()));
        saveButton->setEnabled(false);
    }
}

void MainWindow::onSaveToFile()
{
    if (lastResult.isEmpty()) {
        QMessageBox::information(this, "Информация", "Нет результата для сохранения");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить результат",
        "result.txt",
        "Text Files (*.txt);;All Files (*)"
        );

    if (fileName.isEmpty()) {
        return;  // Пользователь отменил
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);

    out << "========================================\n";
    out << "Результат вычисления алгоритмической арифметики\n";
    out << "Дата: " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") << "\n";
    out << "Тип: " << ui->typeComboBox->currentText() << "\n";
    out << "Функция: " << ui->funcComboBox->currentText() << "\n";
    out << "========================================\n\n";

    out << "Входные данные:\n";
    for (int i = 0; i < fieldEditors.size(); i++) {
        out << "  " << char('A' + i) << ": " << fieldEditors[i]->text() << "\n";
    }
    out << "\n";

    out << "Результат:\n";
    out << lastResult << "\n";
    out << "\n========================================\n";

    file.close();

    QMessageBox::information(this, "Успех", "Результат сохранён в:\n" + fileName);
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
        rx.setPattern(R"(^[-x^0-9+/ ]*$)");

    auto *validator = new QRegularExpressionValidator(rx, this);

    for (const QString &label : labels) {
        auto *edit = new QLineEdit(this);
        edit->setValidator(validator);
        edit->setPlaceholderText(label);

        // ✅ Адаптивная ширина полей
        if (type == "Polynomial") {
            edit->setMinimumWidth(300);
            edit->setMaximumWidth(600);
            edit->setFont(QFont("Consolas", 10));
            edit->setToolTip("Ввод: коэффициенты через пробел, от старшей степени. Пример: '1 0 -1' = x² - 1");
        } else {
            edit->setMinimumWidth(150);
            edit->setMaximumWidth(300);
        }
        edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        dynamicLayout->addRow(label + ":", edit);
        fieldEditors.append(edit);
    }

    qDebug() << "Created" << fieldEditors.size() << "fields for" << type;
}

RationalNumber MainWindow::parseRational(const QString &s)
{
    QStringList parts = s.split('/');
    if (parts.size() == 2 && !parts[1].isEmpty()) {
        return RationalNumber(parts[0], parts[1]);
    }
    return RationalNumber(s, "1");
}

PolynomialNumber MainWindow::parsePolynomial(const QString &s) {
    QString trimmed = s.trimmed();
    if (trimmed.contains('x'))
        return parsePolynomialExpr(trimmed);

    QStringList coeffStrs = trimmed.split(' ', Qt::SkipEmptyParts);
    if (coeffStrs.isEmpty())
        return PolynomialNumber();

    std::vector<RationalNumber> coeffs;
    for (const QString &c : coeffStrs)
        coeffs.push_back(parseRational(c));

    PolynomialNumber result;
    result.degree = static_cast<int>(coeffs.size()) - 1;
    result.coefficients = coeffs;
    return result;
}

PolynomialNumber MainWindow::parsePolynomialExpr(const QString &expr) {
    QString s = expr;
    s.remove(' ');
    if (s.isEmpty()) return PolynomialNumber();

    if (s[0] != '+' && s[0] != '-') s.prepend('+');

    QMap<int, QString> termMap;
    QRegularExpression re(R"(([+-])([^+-]+))");
    QRegularExpressionMatchIterator it = re.globalMatch(s);

    while (it.hasNext()) {
        QRegularExpressionMatch m = it.next();
        QString sign = m.captured(1);
        QString body = m.captured(2);
        if (body.isEmpty()) continue;

        int degree;
        QString coeffStr;

        int xi = body.indexOf('x');
        if (xi >= 0) {
            coeffStr = body.left(xi);
            if (coeffStr.isEmpty()) coeffStr = "1";
            if (xi + 1 < body.size() && body[xi + 1] == '^')
                degree = body.mid(xi + 2).toInt();
            else
                degree = 1;
        } else {
            degree = 0;
            coeffStr = body;
        }

        termMap[degree] = (sign == "-") ? ("-" + coeffStr) : coeffStr;
    }

    if (termMap.isEmpty()) return PolynomialNumber();

    int maxDeg = termMap.lastKey();
    std::vector<RationalNumber> coeffs(maxDeg + 1, RationalNumber("0", "1"));
    for (auto jt = termMap.cbegin(); jt != termMap.cend(); ++jt)
        coeffs[maxDeg - jt.key()] = parseRational(jt.value());

    PolynomialNumber result;
    result.degree = maxDeg;
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
            return Polinomial().DEG_P_N(a).toString();
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

void MainWindow::saveResultToFile(const QString &type, const QString &func, const QStringList &inputs, const QString &result)
{
    QFile file("results.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Не удалось открыть results.txt для записи";
        return;
    }
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "\n";
    out << "Тип: " << type << " | Функция: " << func << "\n";
    out << "Входные данные: " << inputs.join(", ") << "\n";
    out << "Результат: " << result << "\n";
    out << "---\n";
}
