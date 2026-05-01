#ifndef INTEGER_H
#define INTEGER_H

#include "number_structures.h"
#include "natural.h"

class Integer : public Natural
{
public:
    Integer();

    Number ABS_Z_N(const IntegerNumber &num);

    int SGN_Z_D(const IntegerNumber &num);

    IntegerNumber MUL_ZM_Z(const IntegerNumber &num);

    IntegerNumber TRANS_N_Z(const Number &num);

    Number TRANS_Z_N(const IntegerNumber &num);

    IntegerNumber ADD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    IntegerNumber SUB_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    IntegerNumber MUL_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    IntegerNumber DIV_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    IntegerNumber MOD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);
};
#endif // INTEGER_H
