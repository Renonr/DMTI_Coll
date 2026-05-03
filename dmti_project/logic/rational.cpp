#include "rational.h"

Rational::Rational() {}

RationalNumber Rational::MUL_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2){

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

// Q-1: RED_Q_Q — сокращение дроби
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
