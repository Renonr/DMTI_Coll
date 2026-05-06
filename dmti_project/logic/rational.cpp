#include "rational.h"

Rational::Rational() {}

// #26 Q-2
// Проверка сокращенного дробного на целое
// Сериков Владислав 5387
bool Rational::INT_Q_B(const RationalNumber &frac)
{
    return false;
}

// #27 Q-3
// Преобразование целого в дробное
// Вековищев Кирилл 5387
RationalNumber Rational::TRANS_Z_Q(const IntegerNumber &num)
{
    return RationalNumber();
}

// #28 Q-4
// Преобразование сокращённого дробного в целое
// Ковалёв Иван 5387
IntegerNumber Rational::TRANS_Q_Z(const RationalNumber &frac)
{
    return IntegerNumber();
}

// #29 Q-5
// Сложение дробей
// Клочкова Лидия 5387
RationalNumber Rational::ADD_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    return RationalNumber();
}

// #30 Q-6
// Вычитание дробей
// Палешева Ариадна 5387
RationalNumber Rational::SUB_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    return RationalNumber();
}

// #31 Q-7
// Умножение дробей
// Кушаев Дмитрий 5387
RationalNumber Rational::MUL_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2){

    // по умолчанию я сокращаю дроби, чтобы вычисления были
    // менее затратными по ресурсам
    // но, возможно, это не подразумевается самой функцией
    // а может и вовсе сокращение более затратно, чем умножение))

    RationalNumber red_frac1 = RED_Q_Q(frac1);
    RationalNumber red_frac2 = RED_Q_Q(frac2);

    IntegerNumber res_numer = MUL_ZZ_Z(red_frac1.numerator, red_frac2.numerator);

    Number res_denom = MUL_NN_N(red_frac1.denominator, red_frac2.denominator);

    RationalNumber result;

    result.numerator = res_numer;
    result.denominator = res_denom;

    result = RED_Q_Q(result);

    return result;
}

// #25 Q-1
// Сокращение дроби
// Степанов Леонид 5387
RationalNumber Rational::RED_Q_Q(const RationalNumber &frac) {
    Number abs_num = ABS_Z_N(frac.numerator);
    Number gcd = GCF_NN_N(abs_num, frac.denominator);

    IntegerNumber gcd_int = TRANS_N_Z(gcd);

    RationalNumber result;
    result.numerator = DIV_ZZ_Z(frac.numerator, gcd_int);

    IntegerNumber den_int = TRANS_N_Z(frac.denominator);
    IntegerNumber new_den = DIV_ZZ_Z(den_int, gcd_int);
    result.denominator = TRANS_Z_N(new_den);

    return result;
}

// #32 Q-8
// Деление дробей
// Грачева Елизавета 5387
RationalNumber Rational::DIV_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    return RationalNumber();
}
