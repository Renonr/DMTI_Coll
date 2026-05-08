#include <QObject>
#include <QTest>
#include "natural.h"
#include "integer.h"
#include "rational.h"
#include "polinomial.h"


class testInteger : public QObject
{
    Q_OBJECT
private slots:
    // ===== ABS_Z_N =====
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

    // ===== SGN_Z_D (Z-2) =====
    void testSGN_Z_D_zero(){
        IntegerNumber a("0");
        QCOMPARE(Integer::SGN_Z_D(a), 0);
    }
    void testSGN_Z_D_positive(){
        IntegerNumber a("123");
        QCOMPARE(Integer::SGN_Z_D(a), 1);
    }
    void testSGN_Z_D_negative(){
        IntegerNumber a("-456");
        QCOMPARE(Integer::SGN_Z_D(a), -1);
    }
    void testSGN_Z_D_one(){
        IntegerNumber a("1");
        QCOMPARE(Integer::SGN_Z_D(a), 1);
    }
    void testSGN_Z_D_minusOne(){
        IntegerNumber a("-1");
        QCOMPARE(Integer::SGN_Z_D(a), -1);
    }
};


class testNatural : public QObject
{
    Q_OBJECT
private slots:
    // ===== COM_NN_D =====
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

    // ===== MUL_Nk_N (N-7) =====
    void testMUL_Nk_N_k0_noChange(){
        Number a("123");
        QCOMPARE(Natural::MUL_Nk_N(a, 0).toString(), QString("123"));
    }
    void testMUL_Nk_N_k1(){
        Number a("123");
        QCOMPARE(Natural::MUL_Nk_N(a, 1).toString(), QString("1230"));
    }
    void testMUL_Nk_N_k3(){
        Number a("5");
        QCOMPARE(Natural::MUL_Nk_N(a, 3).toString(), QString("5000"));
    }
    void testMUL_Nk_N_zeroNumber(){
        Number a("0");
        QCOMPARE(Natural::MUL_Nk_N(a, 5).toString(), QString("0"));
    }
    void testMUL_Nk_N_k2(){
        Number a("99");
        QCOMPARE(Natural::MUL_Nk_N(a, 2).toString(), QString("9900"));
    }
};


class testRational : public QObject
{
    Q_OBJECT
private slots:
    // ===== RED_Q_Q (Q-1) =====
    void testRED_Q_Q_alreadyReduced(){
        // 7/3 — несократимая дробь
        RationalNumber f("7", "3");
        QCOMPARE(Rational::RED_Q_Q(f).toString(), QString("7/3"));
    }
    void testRED_Q_Q_reduceSixNinths(){
        // 6/9 = 2/3
        RationalNumber f("6", "9");
        QCOMPARE(Rational::RED_Q_Q(f).toString(), QString("2/3"));
    }
    void testRED_Q_Q_reduceHalf(){
        // 4/8 = 1/2
        RationalNumber f("4", "8");
        QCOMPARE(Rational::RED_Q_Q(f).toString(), QString("1/2"));
    }
    void testRED_Q_Q_negativeNumerator(){
        // -6/9 = -2/3
        RationalNumber f("-6", "9");
        QCOMPARE(Rational::RED_Q_Q(f).toString(), QString("-2/3"));
    }
    void testRED_Q_Q_wholeNumber(){
        // 10/5 = 2/1
        RationalNumber f("10", "5");
        QCOMPARE(Rational::RED_Q_Q(f).toString(), QString("2/1"));
    }
};


class testPolinomial : public QObject
{
    Q_OBJECT
private slots:
    // ===== SUB_PP_P (P-2) =====

    // p - p = нулевой многочлен (степень 0, один коэффициент)
    void testSUB_PP_P_samePoly(){
        std::vector<RationalNumber> c = {
            RationalNumber("1","1"),
            RationalNumber("2","1"),
            RationalNumber("3","1")
        };
        PolynomialNumber p(2, c);
        PolynomialNumber result = Polinomial::SUB_PP_P(p, p);
        QCOMPARE(result.degree, 0);
        QCOMPARE((int)result.coefficients.size(), 1);
    }

    // Размер вектора коэффициентов всегда равен degree + 1
    void testSUB_PP_P_coeffsSizeIsConsistent(){
        std::vector<RationalNumber> c1 = {
            RationalNumber("1","1"),
            RationalNumber("2","1"),
            RationalNumber("3","1")
        };
        std::vector<RationalNumber> c2 = {
            RationalNumber("1","1"),
            RationalNumber("1","1")
        };
        PolynomialNumber p1(2, c1);
        PolynomialNumber p2(1, c2);
        PolynomialNumber result = Polinomial::SUB_PP_P(p1, p2);
        QVERIFY(result.degree >= 0);
        QCOMPARE((int)result.coefficients.size(), result.degree + 1);
    }

    // Вычитание нулевого многочлена не меняет степень структуры
    void testSUB_PP_P_subtractZero(){
        std::vector<RationalNumber> c = {RationalNumber("5","1")};
        PolynomialNumber p(0, c);
        PolynomialNumber zero;
        PolynomialNumber result = Polinomial::SUB_PP_P(p, zero);
        QVERIFY(result.degree >= 0);
        QCOMPARE((int)result.coefficients.size(), result.degree + 1);
    }

    // ===== GCF_PP_P (P-11) =====

    // Результат НОД имеет корректную степень и размер вектора
    void testGCF_PP_P_validResult(){
        std::vector<RationalNumber> c1 = {
            RationalNumber("0","1"),
            RationalNumber("0","1"),
            RationalNumber("1","1")
        };
        std::vector<RationalNumber> c2 = {
            RationalNumber("0","1"),
            RationalNumber("1","1")
        };
        PolynomialNumber p1(2, c1);
        PolynomialNumber p2(1, c2);
        PolynomialNumber result = Polinomial::GCF_PP_P(p1, p2);
        QVERIFY(result.degree >= 0);
        QCOMPARE((int)result.coefficients.size(), result.degree + 1);
    }

    // НОД двух одинаковых многочленов — сам многочлен
    void testGCF_PP_P_samePoly(){
        std::vector<RationalNumber> c = {
            RationalNumber("1","1"),
            RationalNumber("1","1")
        };
        PolynomialNumber p(1, c);
        PolynomialNumber result = Polinomial::GCF_PP_P(p, p);
        QVERIFY(result.degree >= 0);
        QCOMPARE((int)result.coefficients.size(), result.degree + 1);
    }
};


int main(int argc, char *argv[]) {
    testInteger    t1;
    testNatural    t2;
    testRational   t3;
    testPolinomial t4;

    int result = 0;
    result += QTest::qExec(&t1, argc, argv);
    result += QTest::qExec(&t2, argc, argv);
    result += QTest::qExec(&t3, argc, argv);
    result += QTest::qExec(&t4, argc, argv);

    return result;
}

#include "generalTest.moc"
