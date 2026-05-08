#include "integer.h"

Integer::Integer() {}

// #15 Z-1
// Абсолютная величина числа
// Баданюк Валерий 5387
Number Integer::ABS_Z_N(const IntegerNumber &num) {
    Number res;
    res.n = num.n;
    res.digits = num.digits;
    return res;
}

// #17 Z-3
// Умножение целого на (-1)
// Сериков Владислав 5387
IntegerNumber Integer::MUL_ZM_Z(const IntegerNumber &num)
{
    IntegerNumber result = num;

    if (result.n == 0 && result.digits[0] == 0){
        result.is_neg = false;
    } else{
        result.is_neg = !result.is_neg;
    }

    return result;
}

// #18 Z-4
// Преобразование натурального в целое
// Вековищев Кирилл 5387
IntegerNumber Integer::TRANS_N_Z(const Number &num)
{
    IntegerNumber result;
    result.is_neg = false;
    result.n = num.n;
    result.digits = num.digits;
    return result;
}

// #19 Z-5
// Преобразование целого в натуральное
// Ковалёв Иван 5387
Number Integer::TRANS_Z_N(const IntegerNumber &num)
{
    Number result;
    result.n = num.n;
    result.digits = num.digits;
    return result;
}

// #20 Z-6
// Сложение целых чисел
// Клочкова Лидия 5387 (Ковалев Иван)
IntegerNumber Integer::ADD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    Number abs1 = ABS_Z_N(num1);
    Number abs2 = ABS_Z_N(num2);
    int sign1 = SGN_Z_D(num1);
    int sign2 = SGN_Z_D(num2);

    if (sign1 == sign2) {
        Number sum = ADD_NN_N(abs1, abs2);
        IntegerNumber result = TRANS_N_Z(sum);
        if (sign1 == -1) {
            result = MUL_ZM_Z(result);
        }
        return result;
    }

    int cmp = COM_NN_D(abs1, abs2);

    if (cmp == 0) {
        return IntegerNumber("0");
    }

    Number diff;
    int result_sign;

    diff = SUB_NN_N(abs1, abs2);

    if (cmp == 2) {
        result_sign = sign1;
    } else {
        result_sign = sign2;
    }

    IntegerNumber result = TRANS_N_Z(diff);

    if (result_sign == -1) {
        result = MUL_ZM_Z(result);
    }

    return result;
}

// #21 Z-7
// Вычитание целых чисел
// Палешева Ариадна 5387 (Ковалев Иван)
IntegerNumber Integer::SUB_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    IntegerNumber neg_num2 = MUL_ZM_Z(num2);
    return ADD_ZZ_Z(num1, neg_num2);
}

// #22 Z-8
// Умножение целых чисел
// Кушаев Дмитрий 5387
IntegerNumber Integer::MUL_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2){

    bool is_negative = false;

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

// #16 Z-2
// Знак целого числа
// Степанов Леонид 5387
int Integer::SGN_Z_D(const IntegerNumber &num) {
    if (num.n == 0 && num.digits.size() == 1 && num.digits[0] == 0) return 0;
    return num.is_neg ? -1 : 1;
}

// #24 Z-10
// Остаток от деления целого на целое
// Баданюк Валерий 5387
IntegerNumber Integer::MOD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2) {
    IntegerNumber q = DIV_ZZ_Z(num1, num2);
    IntegerNumber r = SUB_ZZ_Z(num1, MUL_ZZ_Z(q, num2));
    // num1 = num2*q + r

    if (r.is_neg) {
        IntegerNumber one("1");
        q = num2.is_neg ? ADD_ZZ_Z(q, one) : SUB_ZZ_Z(q, one);

        r = SUB_ZZ_Z(num1, MUL_ZZ_Z(q, num2));
    }

    return r;
}

// #23 Z-9
// Частное от деления целого на целое
// Грачева Елизавета 5387 (Ковалев Иван)
IntegerNumber Integer::DIV_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    Number absInt1 = ABS_Z_N(num1);
    Number absInt2 = ABS_Z_N(num2);
    Number result = DIV_NN_N(absInt1, absInt2);

    int sign1 = SGN_Z_D(num1);
    int sign2 = SGN_Z_D(num2);

    if(COM_NN_D(MUL_NN_N(absInt2, result), absInt1) == 0){
        return sign1 == sign2 ? TRANS_N_Z(result) : MUL_ZM_Z(TRANS_N_Z(result));
    }

    if ((sign1 == -1 && sign2 == 1)){
        result = ADD_1N_N(result);
        return MUL_ZM_Z(TRANS_N_Z(result));
    }else if(sign1 == sign2 && sign1 == -1){
        result = ADD_1N_N(result);
        return TRANS_N_Z(result);
    }else if(sign1 == 1 && sign2 == -1){
        return MUL_ZM_Z(TRANS_N_Z(result));
    }else{
        return TRANS_N_Z(result);
    }
}

