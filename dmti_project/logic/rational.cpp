#include "rational.h"

Rational::Rational() {}

// #26 Q-2
// Проверка сокращенного дробного на целое
// Сериков Владислав 5387 (Ковалев Иван)
bool Rational::INT_Q_B(const RationalNumber &frac)
{
    Number denom = frac.denominator;
    if(denom.n == 0 && denom.digits[0] == 1){
        return true;
    }
    return false;
}

// #27 Q-3
// Преобразование целого в дробное
// Вековищев Кирилл 5387
RationalNumber Rational::TRANS_Z_Q(const IntegerNumber &num)
{
    RationalNumber result;
    result.numerator = num;
    result.denominator = Number("1");
    return result;
}

// #28 Q-4
// Преобразование сокращённого дробного в целое
// Ковалёв Иван 5387
IntegerNumber Rational::TRANS_Q_Z(const RationalNumber &frac)
{
    RationalNumber shortFrac = RED_Q_Q(frac);
    if(INT_Q_B(shortFrac) || (frac.numerator.n == 0 && frac.numerator.digits[0] == 0)){
        return shortFrac.numerator;
    } else{
        throw std::invalid_argument("Число не является целым");
    }
}

// #29 Q-5
// Сложение дробей
// Клочкова Лидия 5387 (Ковалев Иван)
RationalNumber Rational::ADD_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    Number fDenomerator1 = frac1.denominator;
    Number fDenomerator2 = frac2.denominator;

    if(COM_NN_D(fDenomerator1, fDenomerator2) == 0){
        IntegerNumber sumNumerator = ADD_ZZ_Z(frac1.numerator, frac2.numerator);
        return RationalNumber(sumNumerator, fDenomerator1);
    }

    Number generalDenom = LCM_NN_N(fDenomerator1, fDenomerator2);

    IntegerNumber fMultply = TRANS_N_Z(DIV_NN_N(generalDenom, fDenomerator1));
    IntegerNumber sMultply = TRANS_N_Z(DIV_NN_N(generalDenom, fDenomerator2));

    fMultply = MUL_ZZ_Z(frac1.numerator, fMultply);
    sMultply = MUL_ZZ_Z(frac2.numerator, sMultply);

    return RationalNumber(ADD_ZZ_Z(fMultply, sMultply), generalDenom);
}

// #30 Q-6
// Вычитание дробей
// Палешева Ариадна 5387 (Ковалев Иван)
RationalNumber Rational::SUB_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    RationalNumber negFrac2 = RationalNumber(MUL_ZM_Z(frac2.numerator), frac2.denominator);
    return ADD_QQ_Q(frac1, negFrac2);
}

// #31 Q-7
// Умножение дробей
// Кушаев Дмитрий 5387
RationalNumber Rational::MUL_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2){

    // При умножении дробей они сокращаются. Результат также сокращён

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
// Грачева Елизавета 5387 (Ковалев Иван)
RationalNumber Rational::DIV_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2)
{
    if (COM_NN_D(ABS_Z_N(frac2.numerator), Number("0")) == 0) {
        throw std::invalid_argument("Деление на ноль");
    }

    Number revDenominator = TRANS_Z_N(frac2.numerator);
    IntegerNumber revNumerator = TRANS_N_Z(frac2.denominator);
    if(SGN_Z_D(frac2.numerator) == -1){
        revNumerator = MUL_ZM_Z(revNumerator);
    }

    RationalNumber reverseFrac2 = RationalNumber(revNumerator, revDenominator);

    return MUL_QQ_Q(frac1, reverseFrac2);
}
