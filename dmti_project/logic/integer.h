#ifndef INTEGER_H
#define INTEGER_H

#include "number_structures.h"
#include "natural.h"

class Integer : public Natural
{
public:
    Integer();

    static Number ABS_Z_N(const IntegerNumber &num);

    static int SGN_Z_D(const IntegerNumber &num);

    static IntegerNumber MUL_ZM_Z(const IntegerNumber &num);

    static IntegerNumber TRANS_N_Z(const Number &num);

    static Number TRANS_Z_N(const IntegerNumber &num);

    static IntegerNumber ADD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    static IntegerNumber SUB_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    static IntegerNumber MUL_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    static IntegerNumber DIV_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);

    static IntegerNumber MOD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2);
};
#endif // INTEGER_H
