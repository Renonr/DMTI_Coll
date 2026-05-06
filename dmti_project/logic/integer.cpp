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
    return Number();
}

// #20 Z-6
// Сложение целых чисел
// Клочкова Лидия 5387
IntegerNumber Integer::ADD_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    return IntegerNumber();
}

// #21 Z-7
// Вычитание целых чисел
// Палешева Ариадна 5387
IntegerNumber Integer::SUB_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
     // Преобразование IntegerNumber к Integer (предполагается возможность приведения)
    const Integer& a = static_cast<const Integer&>(num1);
    const Integer& b = static_cast<const Integer&>(num2);
    
    // Получение абсолютных значений
    Natural abs1 = a.ABS_Z_N();
    Natural abs2 = b.ABS_Z_N();
    
    // Оба числа равны нулю
    if ((abs1 == Natural(0)) && (abs2 == Natural(0))) {
        return IntegerNumber();
    }
    
    // Первое число равно нулю
    if (abs1 == Natural(0)) {
        return IntegerNumber(b.MUL_ZM_Z());
    }
    
    // Второе число равно нулю
    if (abs2 == Natural(0)) {
        return IntegerNumber(a);
    }
    
    // Оба числа положительные
    if (a.POZ_Z_D() == 1 && b.POZ_Z_D() == 1) {
        if (abs1 > abs2 || abs1 == abs2) {
            Natural resultAbs = abs1 - abs2;
            return IntegerNumber(resultAbs);
        } else {
            Natural resultAbs = abs2 - abs1;
            return IntegerNumber(resultAbs, true); // true обозначает отрицательное число
        }
    }
    
    // Оба числа отрицательные
    if (a.POZ_Z_D() == -1 && b.POZ_Z_D() == -1) {
        if ((abs1 > abs2) || (abs1 == abs2)) {
            Natural resultAbs = abs1 - abs2;
            return IntegerNumber(resultAbs, true);
        } else {
            Natural resultAbs = abs2 - abs1;
            return IntegerNumber(resultAbs);
        }
    }
    
    // Первое положительное, второе отрицательное
    if (a.POZ_Z_D() == 1 && b.POZ_Z_D() == -1) {
        Natural resultAbs = abs1 + abs2;
        return IntegerNumber(resultAbs);
    }
    
    // Первое отрицательное, второе положительное
    if (a.POZ_Z_D() == -1 && b.POZ_Z_D() == 1) {
        Natural resultAbs = abs1 + abs2;
        return IntegerNumber(resultAbs, true);
    }
    
    return IntegerNumber();
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
// Грачева Елизавета 5387
IntegerNumber Integer::DIV_ZZ_Z(const IntegerNumber &num1, const IntegerNumber &num2)
{
    return IntegerNumber();
}

