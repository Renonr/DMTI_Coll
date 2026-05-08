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
    Number result;
    bool is_first = true;

    for (int i = num2.n; i >= 0; i--){
        Number curr_num = MUL_ND_N(num1, num2.digits[i]);
        curr_num = MUL_Nk_N(curr_num, num2.n - i);

        if (!NZER_N_B(curr_num)){
            continue;
        }

        if (is_first){
            result = curr_num;
            is_first = false;
        } else{
            result = ADD_NN_N(result, curr_num);
        }
    }

    return result;
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
    }else{
        return Number("0");
    }
}

// #10 N-10
// Вычисление первой цифры деления
// Ковалёв Иван 5387
Number Natural::DIV_NN_Dk(const Number &num1, const Number &num2, int k)
{
    if (COM_NN_D(num1, num2) == 0){
        return Number("1");
    }

    if (NZER_N_B(num1) == false){
        return Number("0");
    }

    Number biggest = (COM_NN_D(num1, num2) == 2) ? num1 : num2;
    Number smaller = (COM_NN_D(num1, num2) == 1) ? num1 : num2;

    smaller = MUL_Nk_N(smaller, k);
    int d = 1;
    while (COM_NN_D(biggest, MUL_ND_N(smaller, d + 1)) != 1){
        d++;
    }

    if (COM_NN_D(biggest, MUL_ND_N(smaller, d)) == 1){
        return Number("0");
    }

    return Number(QString::number(d)[0]);
}

// #11 N-11
// Неполное частного от деления с остатком
// Клочкова Лидия 5387 (Ковалев Иван)
Number Natural::DIV_NN_N(const Number &num1, const Number &num2)
{
    if(COM_NN_D(num1, num2) == 1){
        return Number("0");
    }

    if(!NZER_N_B(num2)){
        throw std::invalid_argument("На ноль делить нельзя!");
    }

    int k = num1.n - num2.n;

    Number multed;
    Number d;
    Number dividend = Number(num1);
    Number result = Number("0");

    while(k >= 0){
        d = DIV_NN_Dk(dividend, num2, k);
        multed = MUL_Nk_N(d, k);
        result = ADD_NN_N(result, multed);
        dividend = SUB_NDN_N(dividend, MUL_Nk_N(num2, k), d.digits[0]);
        k--;
    }
    return result;
}

// #12 N-12
// Остаток от деления
// Палешева Ариадна (Ковалев Иван)
Number Natural::MOD_NN_N(const Number &num1, const Number &num2)
{
    if(COM_NN_D(num1, num2) == 1){
        return num1;
    }

    if(!NZER_N_B(num2)){
        throw std::invalid_argument("На ноль делить нельзя!");
    }

    int k = num1.n - num2.n;

    Number multed;
    Number d;
    Number dividend = Number(num1);
    Number result = Number("0");

    while(k >= 0){
        d = DIV_NN_Dk(dividend, num2, k);
        multed = MUL_Nk_N(d, k);
        result = ADD_NN_N(result, multed);
        dividend = SUB_NDN_N(dividend, MUL_Nk_N(num2, k), d.digits[0]);
        k--;
    }
    return dividend;
}

// #4 N-4
// Сложение натуральных чисел
// Кушаев Дмитрий 5387
Number Natural::ADD_NN_N(const Number &num1, const Number &num2) {
    const Number *bigger_ptr = (num1.digits.size() >= num2.digits.size()) ? &num1 : &num2;
    const Number *smaller_ptr = (bigger_ptr == &num1) ? &num2 : &num1;

    std::vector<int> result;
    int to_next = 0;

    int i = bigger_ptr->digits.size() - 1;
    int j = smaller_ptr->digits.size() - 1;

    while (i >= 0 || to_next > 0) {
        int sum = to_next;

        if (i >= 0) sum += bigger_ptr->digits[i--];
        if (j >= 0) sum += smaller_ptr->digits[j--];

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
// Грачева Елизавета 5387 (Ковалев Иван)
Number Natural::SUB_NN_N(const Number &num1, const Number &num2)
{
    if (COM_NN_D(num1, num2) == 0){
        return Number();
    }

    Number biggest = (COM_NN_D(num1, num2) == 2) ? num1 : num2;
    Number smaller = (COM_NN_D(num1, num2) == 1) ? num1 : num2;

    int current_biggest = biggest.n;
    for (int i = smaller.n; i >= 0; i--){
        if (biggest.digits[current_biggest] >= smaller.digits[i]){
            biggest.digits[current_biggest] -= smaller.digits[i];
        } else{
            int step = 1;
            while(biggest.digits[current_biggest - step] == 0){
                biggest.digits[current_biggest - step] = 9;
                step++;
            }
            biggest.digits[current_biggest - step] -= 1;
            biggest.digits[current_biggest] += 10;
            biggest.digits[current_biggest] -= smaller.digits[i];
        }
        current_biggest--;
    }

    while (biggest.digits.size() > 1 && biggest.digits.front() == 0) {
        biggest.digits.erase(biggest.digits.begin());
        biggest.n--;
    }

    return biggest;
}

// #13 N-13
// НОД натуральных чисел
// Кушаев Дмитрий 5387 (Ковалев Иван)
Number Natural::GCF_NN_N(const Number &num1, const Number &num2)
{
    bool is_num1_zero = !NZER_N_B(num1);
    bool is_num2_zero = !NZER_N_B(num2);

    if (is_num1_zero && is_num2_zero) {
        return Number("0");
    }
    if (is_num1_zero) return num2;
    if (is_num2_zero) return num1;

    Number a = num1;
    Number b = num2;

    while (NZER_N_B(b)) {
        Number temp = b;
        b = MOD_NN_N(a, b);
        a = temp;
    }

    return a;
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
// Грачева Елизавета 5387 (Ковалев Иван)
Number Natural::LCM_NN_N(const Number &num1, const Number &num2)
{
    return DIV_NN_N((MUL_NN_N(num1, num2)), GCF_NN_N(num1, num2));
}
