#include "natural.h"

Natural::Natural() {}

int Natural::COM_NN_D(const Number &num1, const Number &num2)
{
    if (num1.n > num2.n){
        return 2;
    } else if (num2.n > num1.n){
        return 1;
    } else{
        for(int i = 0; i < num1.n; i++){
            if (num1.digits[i] > num2.digits[i]){
                return 2;
            } else if (num1.digits[i] < num2.digits[i])
                return 1;
        }
        return 0;
    }
}

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

Number Natural::ADD_NN_N(const Number &num1, const Number &num2){
    const Number *bigger_ptr = (COM_NN_D(num1, num2) == 1) ? &num2 : &num1;
    const Number *smaller_ptr = (bigger_ptr == &num1) ? &num2 : &num1;

    std::vector<int> result;

    int to_next;

    int i = bigger_ptr->n - 1;
    int j = smaller_ptr->n - 1;

    int sum;

    int sum = 0;

    while(i >= 0 || to_next > 0){

        sum = to_next;

        if(i >= 0) sum += bigger_ptr->digits[i--];
        if(j >= 0) sum += smaller_ptr->digits[j--];

        result.push_back(sum % 10);

        to_next = sum / 10;
    }

    std::reverse(result.begin(), result.end());

    Number resNum("");
    resNum.digits = result;
    resNum.n = result.size() - 1;

    return resNum;
}

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
