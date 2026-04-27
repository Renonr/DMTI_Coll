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
