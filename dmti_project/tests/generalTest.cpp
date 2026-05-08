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
    // ===== ТЕСТЫ ДЛЯ ABS_Z_N ===== 
    void testABS_Z_N_neg(){
        IntegerNumber a("-512");
        QCOMPARE(Integer::ABS_Z_N(a), Number("512"));
    }

    void testABS_Z_N_pos(){
        IntegerNumber a("123");
        QCOMPARE(Integer::ABS_Z_N(a), Number("123"));
    }

    void testABS_Z_N_zero(){
        IntegerNumber a("0");
        QCOMPARE(Integer::ABS_Z_N(a), Number("0"));
    }

    // ===== ТЕСТЫ ДЛЯ MOD_ZZ_Z =====
    void testMOD_ZZ_Z_bothPos(){
        IntegerNumber a("13"), b("10");
        QCOMPARE(Integer::MOD_ZZ_Z(a, b), IntegerNumber("3"));
    }

    void testMOD_ZZ_Z_bothNeg(){
        IntegerNumber a("-13"), b("-10");
        QCOMPARE(Integer::MOD_ZZ_Z(a, b), IntegerNumber("7"));
    }

    void testMOD_ZZ_Z_opposites1(){
        IntegerNumber a("17"), b("-13");
        QCOMPARE(Integer::MOD_ZZ_Z(a, b), IntegerNumber("4"));
    }

    void testMOD_ZZ_Z_opposites2(){
        IntegerNumber a("-17"), b("13");
        QCOMPARE(Integer::MOD_ZZ_Z(a, b), IntegerNumber("9"));
    }
};


class testNatural : public QObject
{
    Q_OBJECT
private slots:
    // ===== ТЕСТЫ ДЛЯ COM_NN_D =====
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

    // ===== ТЕСТЫ ДЛЯ MUL_ND_N =====
    void testMUL_ND_N_smallNum(){
        Number a("5");
        int digit = 9;
        QCOMPARE(Natural::MUL_ND_D(a, digit), 45);
    }

    void testMUL_ND_N_bigNum(){
        Number a("5499");
        int digit = 9;
        QCOMPARE(Natural::MUL_ND_D(a, digit), 49491);
    }

    void testMUL_ND_N_zero(){
        Number a("5499");
        int digit = 0;
        QCOMPARE(Natural::MUL_ND_D(a, digit), 0);
    }

    void testMUL_ND_N_one(){
        Number a("5499");
        int digit = 1;
        QCOMPARE(Natural::MUL_ND_D(a, digit), 5499);
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
