#ifndef RATIONAL_H
#define RATIONAL_H

#include "number_structures.h"
#include "integer.h"

class Rational : public Integer
{
public:
    Rational();

    RationalNumber RED_Q_Q(const RationalNumber &frac);

    bool INT_Q_B(const RationalNumber &frac);

    RationalNumber TRANS_Z_Q(const IntegerNumber &num);

    IntegerNumber TRANS_Q_Z(const RationalNumber &frac);

    RationalNumber ADD_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);

    RationalNumber SUB_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);

    RationalNumber MUL_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);

    RationalNumber DIV_QQ_Q(const RationalNumber &frac1, const RationalNumber &frac2);
};

#endif // RATIONAL_H
