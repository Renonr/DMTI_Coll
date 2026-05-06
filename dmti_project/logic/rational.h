#ifndef RATIONAL_H
#define RATIONAL_H

#include "number_structures.h"
#include "integer.h"

class Rational : public Integer
{
public:
    Rational();

    static RationalNumber RED_Q_Q(const RationalNumber &frac);

    static bool INT_Q_B(const RationalNumber &frac);

    static RationalNumber TRANS_Z_Q(const IntegerNumber &num);

    static IntegerNumber TRANS_Q_Z(const RationalNumber &frac);

    static RationalNumber ADD_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);

    static RationalNumber SUB_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);

    static RationalNumber MUL_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);

    static RationalNumber DIV_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);
};

#endif // RATIONAL_H
