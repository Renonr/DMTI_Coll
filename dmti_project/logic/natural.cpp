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

Number Natural::ADD_NN_N(const Number &num1, const Number &num2){

    const Number *bigger_ptr = (COM_NN_D(num1, num2) == 1) ? &num2 : &num1;
    const Number *smaller_ptr = (bigger_ptr == &num1) ? &num2 : &num1;

    std::vector<int> result;

    int to_next;

    int i = bigger_ptr->digits.size() - 1;
    int j = smaller_ptr->digits.size() - 1;

    while(i >= 0 || to_next > 0){

        int sum = to_next;

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
