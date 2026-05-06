#include "natural.h"

Natural::Natural() {}

// #1 N-1
// Сравнение натуральных чисел
// Ковалёв Иван 5387
int Natural::COM_NN_D(const Number &num1, const Number &num2)
{
    if (num1.n > num2.n){
        return 2;
    } else if (num2.n > num1.n){
        return 1;
    } else{
        for(int i = 0; i <= num1.n; i++){
            if (num1.digits.at(i) > num2.digits.at(i)){
                return 2;
            } else if (num1.digits.at(i) < num2.digits.at(i))
                return 1;
        }
        return 0;
    }
}

// #2 N-2
// Проверка натурального числа на ноль
// Клочкова Лидия 5387 (Ковалёв Иван 5387)
bool Natural::NZER_N_B(const Number &num)
{
    if (num.n == 0 && num.digits[0] == 0){
        return false;
    }
    return true;
}

// #3 N-3
// Добавление единицы к натуральному числу
// Палешева Ариадна 5387 (Ковалёв Иван 5387) 
Number Natural::ADD_1N_N(const Number &num)
{
    Number new_num = num;

    for(int i = new_num.n; i >= 0; i--){
        if (new_num.digits[i] == 9){
            new_num.digits.at(i) = 0;
        } else{
            new_num.digits.at(i) += 1;
            return new_num;
        }
    }

    new_num.n++;
    new_num.digits.insert(new_num.digits.begin(), 1);
    return new_num;
}

// #6 N-6
// Умножение натурального числа на цифру
// Баданюк Валерий 5387
Number Natural::MUL_ND_N(const Number &num, int digit) 
{
    if (digit == 0) return Number();
    if (digit == 1) return Number(num.toString());

    std::vector<int> new_num;
    int in_mind = 0;
    
    for (int i = num.n; i >= 0; i--) {
        int tmp = num.digits[i]*digit + in_mind;
        if (tmp > 9) {
            new_num.push_back(tmp % 10);
            in_mind = tmp / 10;
        } else {
            new_num.push_back(tmp);
            in_mind = 0;
        }      
    }

    if (in_mind > 0) new_num.push_back(in_mind);
    
    QString result;
    result.reserve(new_num.size());
    for (int i = new_num.size()-1; i >= 0; i--) result += QString::number(new_num[i]);

    return Number(result);
}

// #8 N-8
// Умножение натуральных чисел
// Сериков Владислав 5387
Number Natural::MUL_NN_N(const Number &num1, const Number &num2)
{
    return Number();
}

// #9 N-9
// Вычитание из натурального другого натурального
// Вековищев Кирилл
Number Natural::SUB_NDN_N(const Number &num1, const Number &num2, int digit)
{
    if (digit == 0){
        return Number(num1.toString());
    } 
    Number mul_num = MUL_ND_N(num2, digit);
    if (COM_NN_D(num1, mul_num) == 2){
        return SUB_NN_N(num1, mul_num);
    }else if(COM_NN_D(num1, mul_num) == 0){
        return Number("0");
    }else{
        //xz что возвращать, если num1 < num2 * digit, по условию задачи ничего не сказано 
    }

}

// #10 N-10
// Вычисление первой цифры деления
// Ковалёв Иван 5387
Number Natural::DIV_NN_Dk(const Number &num1, const Number &num2, int k)
{
    return Number();
}

// #11 N-11
// Неполное частного от деления с остатком
// Клочкова Лидия 5387
Number Natural::DIV_NN_N(const Number &num1, const Number &num2)
{
    return Number();
}

// #12 N-12
// Остаток от деления
// Палешева Ариадна
Number Natural::MOD_NN_N(const Number &num1, const Number &num2)
{
    return Number();
}

// #4 N-4
// Сложение натуральных чисел
// Кушаев Дмитрий 5387
Number Natural::ADD_NN_N(const Number &num1, const Number &num2){
    const Number *bigger_ptr = (COM_NN_D(num1, num2) == 1) ? &num2 : &num1;
    const Number *smaller_ptr = (bigger_ptr == &num1) ? &num2 : &num1;

    std::vector<int> result;

    int to_next = 0;

    int i = bigger_ptr->n - 1;
    int j = smaller_ptr->n - 1;

    int sum = 0;

    while(i >= 0 || to_next > 0){

        sum = to_next;

        if(i >= 0) sum += bigger_ptr->digits[i--];
        if(j >= 0) sum += smaller_ptr->digits[j--];

        result.push_back(sum % 10);

        to_next = sum / 10;
    }

    std::reverse(result.begin(), result.end());

    Number resNum;
    resNum.digits = result;
    resNum.n = result.size() - 1;

    return resNum;
}

// #5 N-5
// Вычитание натуральных чисел
// Грачева Елизавета 5387
Number Natural::SUB_NN_N(const Number &num1, const Number &num2)
{
    if (COM_NN_D(num1, num2) == 0){
        return Number();
    }

    Number biggest = (COM_NN_D(num1, num2) == 2) ? num1 : num2;
    Number smaller = (COM_NN_D(num1, num2) == 1) ? num1 : num2;

    /*int high = smaller.n;
    for (int i = high; i >= 0; i--){
        if (biggest.digits[i] >= smaller.digits[i]){
            biggest.digits[i] -= smaller.digits[i];
        } else {
            biggest.digits[i] = biggest.digits[i] + 10 - smaller.digits[i];
            biggest.digits[i + 1] -= 1;
        }
    }*/

    return biggest;
}

// #13 N-13
// НОД натуральных чисел
// Кушаев Дмитрий 5387
Number Natural::GCF_NN_N(const Number &num1, const Number &num2){

    bool is_num1_zero = NZER_N_B(num1);
    bool is_num2_zero = NZER_N_B(num2);

    Number GCF;

    if(is_num1_zero && is_num2_zero){
        GCF.digits.push_back(1);
        GCF.n += 1;
        return GCF;
    } else if(is_num1_zero){
        Number GCF(num2);
        return GCF;
    } else if(is_num2_zero){
        Number GCF(num1);
        return GCF;
    }

    const Number *bigger_ptr = (COM_NN_D(num1, num2) == 1) ? &num2 : &num1;
    const Number *smaller_ptr = (bigger_ptr == &num1) ? &num2 : &num1;

    Number curr_remain = MOD_NN_N(*bigger_ptr, *smaller_ptr);
    Number prev_remain = curr_remain;
    Number bigger_num = *smaller_ptr;

    while(NZER_N_B(curr_remain)){

        prev_remain = curr_remain;

        curr_remain = MOD_NN_N(bigger_num, curr_remain);

        bigger_num = prev_remain;
    }

    return prev_remain;
}

// #7 N-7
// Умножение натурального числа на 10^k
// Степанов Леонид 5387
Number Natural::MUL_Nk_N(const Number &num, int k) {
    if (k <= 0) return num;
    if (num.digits.size() == 1 && num.digits[0] == 0) return num;

    Number result = num;
    for (int i = 0; i < k; ++i) {
        result.digits.push_back(0);
    }
    result.n += k;
    return result;
}

// #14 N-14
// НОК натуральных чисел
// Грачева Елизавета 5387
Number Natural::LCM_NN_N(const Number &num1, const Number &num2)
{
    return Number();
}
