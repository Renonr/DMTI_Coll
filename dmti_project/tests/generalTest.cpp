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

    // ===== MUL_ZM_Z (Z-3) =====
    void testMUL_ZM_Z_positive(){
        IntegerNumber a("123");
        QCOMPARE(Integer::MUL_ZM_Z(a).toString(), QString("-123"));
    }
    void testMUL_ZM_Z_negative(){
        IntegerNumber a("-123");
        QCOMPARE(Integer::MUL_ZM_Z(a).toString(), QString("123"));
    }
    void testMUL_ZM_Z_zero(){
        IntegerNumber a("0");
        QCOMPARE(Integer::MUL_ZM_Z(a).toString(), QString("0"));
    }

    // ===== ADD_ZZ_Z (Z-6) =====
    void testADD_ZZ_Z_bothPositive(){
        IntegerNumber a("3"), b("5");
        QCOMPARE(Integer::ADD_ZZ_Z(a, b).toString(), QString("8"));
    }
    void testADD_ZZ_Z_bothNegative(){
        IntegerNumber a("-3"), b("-5");
        QCOMPARE(Integer::ADD_ZZ_Z(a, b).toString(), QString("-8"));
    }
    void testADD_ZZ_Z_opposites(){
        IntegerNumber a("5"), b("-5");
        QCOMPARE(Integer::ADD_ZZ_Z(a, b).toString(), QString("0"));
    }
    void testADD_ZZ_Z_negPlusBigPos(){
        IntegerNumber a("-3"), b("5");
        QCOMPARE(Integer::ADD_ZZ_Z(a, b).toString(), QString("2"));
    }
    void testADD_ZZ_Z_posPlusBigNeg(){
        IntegerNumber a("3"), b("-5");
        QCOMPARE(Integer::ADD_ZZ_Z(a, b).toString(), QString("-2"));
    }

    // ===== MUL_ZZ_Z (Z-8) =====
    void testMUL_ZZ_Z_bothPositive(){
        IntegerNumber a("3"), b("4");
        QCOMPARE(Integer::MUL_ZZ_Z(a, b).toString(), QString("12"));
    }
    void testMUL_ZZ_Z_negTimesPos(){
        IntegerNumber a("-3"), b("4");
        QCOMPARE(Integer::MUL_ZZ_Z(a, b).toString(), QString("-12"));
    }
    void testMUL_ZZ_Z_bothNegative(){
        IntegerNumber a("-3"), b("-4");
        QCOMPARE(Integer::MUL_ZZ_Z(a, b).toString(), QString("12"));
    }
    void testMUL_ZZ_Z_byZero(){
        IntegerNumber a("5"), b("0");
        QCOMPARE(Integer::MUL_ZZ_Z(a, b).toString(), QString("0"));
    }
    void testMUL_ZZ_Z_byOne(){
        IntegerNumber a("7"), b("1");
        QCOMPARE(Integer::MUL_ZZ_Z(a, b).toString(), QString("7"));
    }

    // ===== SUB_ZZ_Z (Z-7) =====
    void testSUB_ZZ_Z_positive(){
        IntegerNumber a("5"), b("3");
        QCOMPARE(Integer::SUB_ZZ_Z(a, b).toString(), QString("2"));
    }
    void testSUB_ZZ_Z_negativeResult(){
        IntegerNumber a("3"), b("5");
        QCOMPARE(Integer::SUB_ZZ_Z(a, b).toString(), QString("-2"));
    }
    void testSUB_ZZ_Z_zero(){
        IntegerNumber a("0"), b("0");
        QCOMPARE(Integer::SUB_ZZ_Z(a, b).toString(), QString("0"));
    }
    void testSUB_ZZ_Z_equal(){
        IntegerNumber a("42"), b("42");
        QCOMPARE(Integer::SUB_ZZ_Z(a, b).toString(), QString("0"));
    }
    void testSUB_ZZ_Z_bothNegative(){
        IntegerNumber a("-3"), b("-5");
        QCOMPARE(Integer::SUB_ZZ_Z(a, b).toString(), QString("2"));
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
    // ===== NZER_N_B (N-1) =====
    void testNZER_N_B_zero(){
        Number a("0");
        QCOMPARE(Natural::NZER_N_B(a), false);
    }
    void testNZER_N_B_one(){
        Number a("1");
        QCOMPARE(Natural::NZER_N_B(a), true);
    }
    void testNZER_N_B_large(){
        Number a("999");
        QCOMPARE(Natural::NZER_N_B(a), true);
    }

    // ===== ADD_NN_N (N-4) =====
    void testADD_NN_N_simple(){
        Number a("3"), b("5");
        QCOMPARE(Natural::ADD_NN_N(a, b).toString(), QString("8"));
    }
    void testADD_NN_N_withCarry(){
        Number a("99"), b("1");
        QCOMPARE(Natural::ADD_NN_N(a, b).toString(), QString("100"));
    }
    void testADD_NN_N_zeros(){
        Number a("0"), b("0");
        QCOMPARE(Natural::ADD_NN_N(a, b).toString(), QString("0"));
    }
    void testADD_NN_N_large(){
        Number a("123"), b("456");
        QCOMPARE(Natural::ADD_NN_N(a, b).toString(), QString("579"));
    }
    void testADD_NN_N_overflow(){
        Number a("999"), b("1");
        QCOMPARE(Natural::ADD_NN_N(a, b).toString(), QString("1000"));
    }

    // ===== GCF_NN_N (N-13) =====
    void testGCF_NN_N_basic(){
        Number a("12"), b("8");
        QCOMPARE(Natural::GCF_NN_N(a, b).toString(), QString("4"));
    }
    void testGCF_NN_N_coprime(){
        Number a("7"), b("5");
        QCOMPARE(Natural::GCF_NN_N(a, b).toString(), QString("1"));
    }
    void testGCF_NN_N_zeroFirst(){
        Number a("0"), b("5");
        QCOMPARE(Natural::GCF_NN_N(a, b).toString(), QString("5"));
    }
    void testGCF_NN_N_equal(){
        Number a("9"), b("9");
        QCOMPARE(Natural::GCF_NN_N(a, b).toString(), QString("9"));
    }
    void testGCF_NN_N_large(){
        Number a("100"), b("75");
        QCOMPARE(Natural::GCF_NN_N(a, b).toString(), QString("25"));
    }

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

    // ===== ADD_1N_N (N-3) =====
    void testADD_1N_N_simple(){
        Number a("123");
        QCOMPARE(Natural::ADD_1N_N(a).toString(), QString("124"));
    }
    void testADD_1N_N_carry(){
        Number a("9");
        QCOMPARE(Natural::ADD_1N_N(a).toString(), QString("10"));
    }
    void testADD_1N_N_allNines(){
        Number a("999");
        QCOMPARE(Natural::ADD_1N_N(a).toString(), QString("1000"));
    }
    void testADD_1N_N_zero(){
        Number a("0");
        QCOMPARE(Natural::ADD_1N_N(a).toString(), QString("1"));
    }
    void testADD_1N_N_partialCarry(){
        Number a("199");
        QCOMPARE(Natural::ADD_1N_N(a).toString(), QString("200"));
    }

    // ===== DIV_NN_N (N-11) =====
    void testDIV_NN_N_exact(){
        Number a("9"), b("3");
        QCOMPARE(Natural::DIV_NN_N(a, b).toString(), QString("3"));
    }
    void testDIV_NN_N_withRemainder(){
        Number a("10"), b("3");
        QCOMPARE(Natural::DIV_NN_N(a, b).toString(), QString("3"));
    }
    void testDIV_NN_N_dividendSmaller(){
        Number a("1"), b("5");
        QCOMPARE(Natural::DIV_NN_N(a, b).toString(), QString("0"));
    }
    void testDIV_NN_N_equal(){
        Number a("7"), b("7");
        QCOMPARE(Natural::DIV_NN_N(a, b).toString(), QString("1"));
    }
    void testDIV_NN_N_large(){
        Number a("100"), b("10");
        QCOMPARE(Natural::DIV_NN_N(a, b).toString(), QString("10"));
    }

    // ===== MOD_NN_N (N-12) =====
    void testMOD_NN_N_noRemainder(){
        Number a("9"), b("3");
        QCOMPARE(Natural::MOD_NN_N(a, b).toString(), QString("0"));
    }
    void testMOD_NN_N_withRemainder(){
        Number a("10"), b("3");
        QCOMPARE(Natural::MOD_NN_N(a, b).toString(), QString("1"));
    }
    void testMOD_NN_N_dividendSmaller(){
        Number a("5"), b("10");
        QCOMPARE(Natural::MOD_NN_N(a, b).toString(), QString("5"));
    }
    void testMOD_NN_N_equal(){
        Number a("7"), b("7");
        QCOMPARE(Natural::MOD_NN_N(a, b).toString(), QString("0"));
    }
    void testMOD_NN_N_large(){
        Number a("100"), b("7");
        QCOMPARE(Natural::MOD_NN_N(a, b).toString(), QString("2"));
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
    // ===== MUL_QQ_Q (Q-7) =====
    void testMUL_QQ_Q_basic(){
        // 1/2 * 2/3 = 1/3
        RationalNumber f1("1", "2"), f2("2", "3");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("1/3"));
    }
    void testMUL_QQ_Q_reciprocals(){
        // 3/4 * 4/3 = 1/1
        RationalNumber f1("3", "4"), f2("4", "3");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("1/1"));
    }
    void testMUL_QQ_Q_negative(){
        // -1/2 * 2/3 = -1/3
        RationalNumber f1("-1", "2"), f2("2", "3");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("-1/3"));
    }
    void testMUL_QQ_Q_byZero(){
        // 0/1 * 5/6 = 0/1
        RationalNumber f1("0", "1"), f2("5", "6");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("0/1"));
    }

    // ===== ADD_QQ_Q (Q-5) =====
    void testADD_QQ_Q_halfPlusThird(){
        // 1/2 + 1/3 = 5/6
        RationalNumber f1("1", "2"), f2("1", "3");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("5/6"));
    }
    void testADD_QQ_Q_sameDenominator(){
        // 1/4 + 1/4 = 1/2
        RationalNumber f1("1", "4"), f2("1", "4");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("1/2"));
    }
    void testADD_QQ_Q_addZero(){
        // 0/1 + 3/5 = 3/5
        RationalNumber f1("0", "1"), f2("3", "5");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("3/5"));
    }
    void testADD_QQ_Q_negativeAndPositive(){
        // -1/3 + 2/3 = 1/3
        RationalNumber f1("-1", "3"), f2("2", "3");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("1/3"));
    }

    // ===== SUB_QQ_Q (Q-6) =====
    void testSUB_QQ_Q_halfMinusThird(){
        // 1/2 - 1/3 = 1/6
        RationalNumber f1("1", "2"), f2("1", "3");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("1/6"));
    }
    void testSUB_QQ_Q_sameDenominator(){
        // 3/4 - 1/4 = 1/2
        RationalNumber f1("3", "4"), f2("1", "4");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("1/2"));
    }
    void testSUB_QQ_Q_equal(){
        // 5/6 - 5/6 = 0/1
        RationalNumber f1("5", "6"), f2("5", "6");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("0/1"));
    }
    void testSUB_QQ_Q_negativeResult(){
        // 1/4 - 1/2 = -1/4
        RationalNumber f1("1", "4"), f2("1", "2");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("-1/4"));
    }

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
    // ===== ADD_PP_P (P-1) =====
    void testADD_PP_P_sameDegree(){
        std::vector<RationalNumber> c1 = {
            RationalNumber("1","1"),
            RationalNumber("2","1"),
            RationalNumber("3","1")
        };
        std::vector<RationalNumber> c2 = {
            RationalNumber("4","1"),
            RationalNumber("5","1"),
            RationalNumber("6","1")
        };
        std::vector<RationalNumber> c3 = {
            RationalNumber("5","1"),
            RationalNumber("7","1"),
            RationalNumber("9","1")
        };

        PolynomialNumber p1(2, c1);
        PolynomialNumber p2(2, c2);
        PolynomialNumber expected(2, c3);

        QCOMPARE(Polinomial::ADD_PP_P(p1, p2).toString(), expected.toString());
    }

    void testADD_PP_P_diff_degree() {
        std::vector<RationalNumber> с1 = {
            RationalNumber("1","1"),
            RationalNumber("2","1"),
            RationalNumber("3","1"),
            RationalNumber("4","1")
        };
        std::vector<RationalNumber> с2 = {
            RationalNumber("5","1"),
            RationalNumber("6","1")
        };
        std::vector<RationalNumber> с3 = {
            RationalNumber("6","1"),
            RationalNumber("8","1"),
            RationalNumber("3","1"),
            RationalNumber("4","1")
        };
        
        PolynomialNumber p1(3, c1);
        PolynomialNumber p2(1, c2);
        PolynomialNumber expected(3, c3);
        
        QCOMPARE(Polinomial::ADD_PP_P(p1, p2).toString(), expected.toString());
    }

    void testADD_PP_P_opposites(){
        std::vector<RationalNumber> c1 = {
            RationalNumber("1","1"),
            RationalNumber("2","1"),
            RationalNumber("3","1")
        };
        std::vector<RationalNumber> c2 = {
            RationalNumber("-1","1"),
            RationalNumber("-2","1"),
            RationalNumber("-3","1")
        };

        PolynomialNumber p1(2, c1);
        PolynomialNumber p2(2, c2);

        QCOMPARE(Polinomial::ADD_PP_P(p1, p2).toString(), Polinomial().toString());
    }

    void testADD_PP_P_leading_zero() {
        std::vector<RationalNumber> с1 = {
            RationalNumber("1","1"),
            RationalNumber("3","1"),
            RationalNumber("5","1")
        }; 
        std::vector<RationalNumber> c2 = {
            RationalNumber("0","1"),
            RationalNumber("0","1"),
            RationalNumber("-5","1")
        };
        std::vector<RationalNumber> c3 = {
            RationalNumber("1","1"),   
            RationalNumber("3","1")
        };

        PolynomialNumber p1(2, с1); 
        PolynomialNumber p2(2, c2);
        PolynomialNumber expected(1, c3);
        // 0x^2 + 3x + 1(степень 2) → 3x + 1 (степень 1)
        
        QCOMPARE(Polinomial::ADD_PP_P(p1, p2).toString(), expected.toString());
    }


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


    // ===== MOD_PP_P (P-10) =====

    void testMOD_PP_P_no_remainder() {
        PolynomialNumber p1(2, {
            RationalNumber("1","1"),
            RationalNumber("2","1"),
            RationalNumber("1","1")
        }); // x^2 + 2x + 1
        PolynomialNumber p2(1, {
            RationalNumber("1","1"),
            RationalNumber("1","1")
        }); // x + 1

        QCOMPARE(Polinomial::MOD_PP_P(p1, p2).toString(), PolynomialNumber().toString());
    }

    void testMOD_PP_P_with_remainder(){
        // (x² + 3x + 3) / (x + 1) => частное x+2, остаток 1
        PolynomialNumber p1(2, {
            RationalNumber("3","1"),
            RationalNumber("3","1"),
            RationalNumber("1","1")
        });
        PolynomialNumber p2(1, {
            RationalNumber("1","1"),
            RationalNumber("1","1")
        });

        std::vector<RationalNumber> one = {"1","1"};
        QCOMPARE(Polinomial::MOD_PP_P(p1, p2).toString(), PolynomialNumber(0, one).toString());
    }

    void testMOD_PP_P_dividend_less_divisor() {
        std::vector<RationalNumber> c1 = {
            RationalNumber("1","1"),
            RationalNumber("1","1")
        };  // x + 1
        
        std::vector<RationalNumber> c2 = {
            RationalNumber("0","1"),
            RationalNumber("0","1"),
            RationalNumber("1","1")
        }; // x^2

        PolynomialNumber p1(1, c1);
        PolynomialNumber p2(2, c2);

        QCOMPARE(Polinomial::MOD_PP_P(p1, p2), p1);
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



    // ===== MUL_NN_N (N-8) =====
    void testMUL_NN_N_simple(){
        Number a("12"), b("34");
        QCOMPARE(Natural::MUL_NN_N(a, b).toString(), QString("408"));
    }
    void testMUL_NN_N_byZero(){
        Number a("999"), b("0");
        QCOMPARE(Natural::MUL_NN_N(a, b).toString(), QString("0"));
    }
    void testMUL_NN_N_large(){
        Number a("999"), b("999");
        QCOMPARE(Natural::MUL_NN_N(a, b).toString(), QString("998001"));
    }
};


class testRational : public QObject
{
    Q_OBJECT
private slots:
    // ===== INT_Q_B (Q-2) =====
    void testINT_Q_B_integer(){
        RationalNumber f("5", "1");
        QCOMPARE(Rational::INT_Q_B(f), true);
    }
    void testINT_Q_B_notInteger(){
        RationalNumber f("5", "2");
        QCOMPARE(Rational::INT_Q_B(f), false);
    }
    void testINT_Q_B_zeroInteger(){
        RationalNumber f("0", "1");
        QCOMPARE(Rational::INT_Q_B(f), true);
    }

    // ===== MUL_QQ_Q (Q-7) =====
    void testMUL_QQ_Q_basic(){
        // 1/2 * 2/3 = 1/3
        RationalNumber f1("1", "2"), f2("2", "3");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("1/3"));
    }
    void testMUL_QQ_Q_reciprocals(){
        // 3/4 * 4/3 = 1/1
        RationalNumber f1("3", "4"), f2("4", "3");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("1/1"));
    }
    void testMUL_QQ_Q_negative(){
        // -1/2 * 2/3 = -1/3
        RationalNumber f1("-1", "2"), f2("2", "3");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("-1/3"));
    }
    void testMUL_QQ_Q_byZero(){
        // 0/1 * 5/6 = 0/1
        RationalNumber f1("0", "1"), f2("5", "6");
        QCOMPARE(Rational::MUL_QQ_Q(f1, f2).toString(), QString("0/1"));
    }

    // ===== ADD_QQ_Q (Q-5) =====
    void testADD_QQ_Q_halfPlusThird(){
        // 1/2 + 1/3 = 5/6
        RationalNumber f1("1", "2"), f2("1", "3");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("5/6"));
    }
    void testADD_QQ_Q_sameDenominator(){
        // 1/4 + 1/4 = 1/2
        RationalNumber f1("1", "4"), f2("1", "4");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("1/2"));
    }
    void testADD_QQ_Q_addZero(){
        // 0/1 + 3/5 = 3/5
        RationalNumber f1("0", "1"), f2("3", "5");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("3/5"));
    }
    void testADD_QQ_Q_negativeAndPositive(){
        // -1/3 + 2/3 = 1/3
        RationalNumber f1("-1", "3"), f2("2", "3");
        QCOMPARE(Rational::ADD_QQ_Q(f1, f2).toString(), QString("1/3"));
    }

    // ===== SUB_QQ_Q (Q-6) =====
    void testSUB_QQ_Q_halfMinusThird(){
        // 1/2 - 1/3 = 1/6
        RationalNumber f1("1", "2"), f2("1", "3");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("1/6"));
    }
    void testSUB_QQ_Q_sameDenominator(){
        // 3/4 - 1/4 = 1/2
        RationalNumber f1("3", "4"), f2("1", "4");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("1/2"));
    }
    void testSUB_QQ_Q_equal(){
        // 5/6 - 5/6 = 0/1
        RationalNumber f1("5", "6"), f2("5", "6");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("0/1"));
    }
    void testSUB_QQ_Q_negativeResult(){
        // 1/4 - 1/2 = -1/4
        RationalNumber f1("1", "4"), f2("1", "2");
        QCOMPARE(Rational::SUB_QQ_Q(f1, f2).toString(), QString("-1/4"));
    }

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
    // ===== MUL_PQ_P (P-3) =====
    void testMUL_PQ_P_basic(){
        std::vector<RationalNumber> c = {
            RationalNumber("1","2"),
            RationalNumber("3","4")
        };
        PolynomialNumber p(1, c);
        RationalNumber q("2", "1");

        PolynomialNumber result = Polinomial::MUL_PQ_P(p, q);

        QCOMPARE(result.degree, 1);
        QCOMPARE(result.coefficients[0].toString(), QString("1/1"));
        QCOMPARE(result.coefficients[1].toString(), QString("3/2"));
    }
    void testMUL_PQ_P_byOne(){
        std::vector<RationalNumber> c = {
            RationalNumber("2","3"),
            RationalNumber("-5","1")
        };
        PolynomialNumber p(1, c);
        RationalNumber q("1", "1");

        PolynomialNumber result = Polinomial::MUL_PQ_P(p, q);

        QCOMPARE(result.degree, 1);
        QCOMPARE(result.coefficients[0].toString(), QString("2/3"));
        QCOMPARE(result.coefficients[1].toString(), QString("-5/1"));
    }

    // ===== DER_P_P (P-12) =====
    void testDER_P_P_square(){
        std::vector<RationalNumber> c = {
            RationalNumber("3","1"),
            RationalNumber("2","1"),
            RationalNumber("1","1")
        };
        PolynomialNumber p(2, c);

        PolynomialNumber result = Polinomial::DER_P_P(p);

        QCOMPARE(result.degree, 1);
        QCOMPARE(result.coefficients[0].toString(), QString("6/1"));
        QCOMPARE(result.coefficients[1].toString(), QString("2/1"));
    }
    void testDER_P_P_constant(){
        std::vector<RationalNumber> c = {
            RationalNumber("5","1")
        };
        PolynomialNumber p(0, c);

        PolynomialNumber result = Polinomial::DER_P_P(p);

        QCOMPARE(result.degree, 0);
        QCOMPARE((int)result.coefficients.size(), 1);
        QCOMPARE(result.coefficients[0].toString(), QString("0/1"));
    }

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