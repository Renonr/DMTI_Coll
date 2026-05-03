#include "integer.h"

Integer::Integer() {}

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

// Z-2: SGN_Z_D — знак числа: 1 положительное, 0 ноль, -1 отрицательное
int Integer::SGN_Z_D(const IntegerNumber &num) {
    if (num.n == 0 && num.digits.size() == 1 && num.digits[0] == 0) return 0;
    return num.is_neg ? -1 : 1;
}