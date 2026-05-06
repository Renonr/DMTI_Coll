#ifndef NATURAL_H
#define NATURAL_H

#include "number_structures.h"
#include <QString>

class Natural
{
public:
    Natural();

    static int COM_NN_D(const Number &num1, const Number &num2);

    static bool NZER_N_B(const Number &num);

    static Number ADD_1N_N(const Number &num);

    static Number ADD_NN_N(const Number &num1, const Number &num2);

    static Number SUB_NN_N(const Number &num1, const Number &num2);

    static Number MUL_ND_N(const Number &num, int digit);

    static Number MUL_Nk_N(const Number &num, int k);

    static Number MUL_NN_N(const Number &num1, const Number &num2);

    static Number SUB_NDN_N(const Number &num1, const Number &num2, int digit);

    static Number DIV_NN_Dk(const Number &num1, const Number &num2, int k);

    static Number DIV_NN_N(const Number &num1, const Number &num2);

    static Number MOD_NN_N(const Number &num1, const Number &num2);

    static Number GCF_NN_N(const Number &num1, const Number &num2);

    static Number LCM_NN_N(const Number &num1, const Number &num2);
};

#endif // NATURAL_H
