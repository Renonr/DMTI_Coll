#ifndef NATURAL_H
#define NATURAL_H

#include "number_structures.h"
#include <QString>

class Natural
{
public:
    Natural();

    int COM_NN_D(const Number &num1, const Number &num2);

    bool NZER_N_B(const Number &num);

    Number ADD_1N_N(const Number &num);

    Number ADD_NN_N(const Number &num);

    Number SUB_NN_N(const Number &num);

    Number MUL_ND_N(const Number &num, int digit);

    Number MUL_Nk_N(const Number &num, int k);

    Number MUL_NN_N(const Number &num1, const Number &num2);

    Number SUB_NDN_N(const Number &num1, const Number &num2, int digit);

    Number DIV_NN_Dk(const Number &num);

    Number DIV_NN_N(const Number &num);

    Number MOD_NN_N(const Number &num1, const Number &num2);

    Number GCF_NN_N(const Number &num1, const Number &num2);

    Number LCM_NN_N(const Number &num1, const Number &num2);
};

#endif // NATURAL_H
