#include "integer.h"

Integer::Integer() {}

Number Integer::ABS_Z_N(const IntegerNumber &num)
{
    return Number();
}

int Integer::SGN_Z_D(const IntegerNumber &num)
{
    return num.n;
}

IntegerNumber Integer::MUL_ZM_Z(const IntegerNumber &num)
{
    return IntegerNumber();
}

IntegerNumber Integer::TRANS_N_Z(const Number &num)
{
    IntegerNumber result;
    result.is_neg = false;
    result.n = num.n;
    result.digits = num.digits;
    return result;
}

Number Integer::TRANS_Z_N(const IntegerNumber &num)
{
    return Number();
}

IntegerNumber Integer::ADD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    return IntegerNumber();
}

IntegerNumber Integer::SUB_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    return IntegerNumber();
}

IntegerNumber Integer::MUL_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2){

    bool is_negative = false;

    // принял, что POZ_Z_D возвращает 1, если положительное,
    // 0, если равно нулю и -1, если отрицательное
    if(SGN_Z_D(num1) == -1 ^ SGN_Z_D(num2) == -1){ 
        is_negative = true;
    }

    Number nat_num1 = ABS_Z_N(num1);
    Number nat_num2 = ABS_Z_N(num2);

    if(!NZER_N_B(nat_num1) || !NZER_N_B(nat_num2)){
        IntegerNumber zero;
        return zero;
    }

    Number nat_result = MUL_NN_N(nat_num1, nat_num2);

    IntegerNumber int_result = TRANS_N_Z(nat_result);

    if(is_negative){
        int_result = MUL_ZM_Z(int_result);
    }

    return int_result;
}

IntegerNumber Integer::DIV_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    return IntegerNumber();
}

IntegerNumber Integer::MOD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    return IntegerNumber();
}
