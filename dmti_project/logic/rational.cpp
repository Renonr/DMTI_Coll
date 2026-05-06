#include "rational.h"

Rational::Rational() {}

RationalNumber Rational::RED_Q_Q(const RationalNumber &frac)
{
    return RationalNumber();
}

bool Rational::INT_Q_B(const RationalNumber &frac)
{
    return false;
}

RationalNumber Rational::TRANS_Z_Q(const IntegerNumber &num)
{
    return RationalNumber();
}

IntegerNumber Rational::TRANS_Q_Z(const RationalNumber &frac)
{
    return IntegerNumber();
}

RationalNumber Rational::ADD_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    return RationalNumber();
}

RationalNumber Rational::SUB_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    return RationalNumber();
}

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

    // аналогично, результат тоже пытаемся сократить

    result = RED_Q_Q(result);

    return result;
}

RationalNumber Rational::DIV_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    return RationalNumber();
}
