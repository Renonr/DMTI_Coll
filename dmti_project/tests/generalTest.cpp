#include <QObject>
#include <QTest>
#include "natural.h"
#include "integer.h"
//#include "rational.h"
//#include "polinomial.h"


class testInteger : public QObject
{
    Q_OBJECT
private slots:
    // ===== ТЕСТЫ ДЛЯ ABS_Z_N (модуль) =====
    void testABS_Z_N_neg(){
        IntegerNumber a("-512");
        QCOMPARE(Integer::ABS_Z_N(a), Number("512"));
    }

    void testABS_Z_N_poz(){
        IntegerNumber a("123");
        QCOMPARE(Integer::ABS_Z_N(a), Number("123"));
    }

    void testABS_Z_N_zero(){
        IntegerNumber a("0");
        QCOMPARE(Integer::ABS_Z_N(a), Number("0"));
    }
};


class testNatural : public QObject
{
    Q_OBJECT
private slots:
    // ===== ТЕСТЫ ДЛЯ COM_NN_D (сравнение) =====
    void testCOM_NN_D_equal(){
        Number a("123");
        Number b("123");
        QCOMPARE(Natural::COM_NN_D(a, b), 0);
    }

    void testCOM_NN_D_greater(){
        Number a("999");
        Number b("100");
        QCOMPARE(Natural::COM_NN_D(a, b), 2);

        Number c("125");
        Number d("123");
        QCOMPARE(Natural::COM_NN_D(c, d), 2);
    }

    void testCOM_NN_D_less(){
        Number a("100");
        Number b("999");
        QCOMPARE(Natural::COM_NN_D(a, b), 1);
    }
};

int main(int argc, char *argv[]) {
    testInteger t1;
    testNatural t2;

    int result = 0;
    result += QTest::qExec(&t1, argc, argv);  // Запуск Integer
    result += QTest::qExec(&t2, argc, argv);  // Запуск Natural

    return result;
}

#include "generalTest.moc"
