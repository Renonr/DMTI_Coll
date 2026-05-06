#include "polinomial.h"

Polinomial::Polinomial() {}

PolynomialNumber Polinomial::ADD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::SUB_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::MUL_PQ_P(const PolynomialNumber &p, const RationalNumber &q)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::MUL_Pxk_P(const PolynomialNumber &p, const Number &k)
{
    return PolynomialNumber();
}

RationalNumber Polinomial::LED_P_Q(const PolynomialNumber &p)
{
    return RationalNumber();
}

Number Polinomial::DEG_P_N(const PolynomialNumber &p)
{
    return Number();
}

RationalNumber Polinomial::FAC_P_Q(const PolynomialNumber &p)
{
    return RationalNumber();
}


PolynomialNumber Polinomial::MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2){
    return PolynomialNumber();
}
//тут пока ошибка в 46 и 53 строк
/*
PolynomialNumber Polinomial::MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2){

    PolynomialNumber result;

    result.degree = DEG_P_N(p1) + DEG_P_N(p2);

    const PolynomialNumber *bigger_deg = (DEG_P_N(p1) > DEG_P_N(p2)) ? &p1 : &p2;
    const PolynomialNumber *smaller_deg = (bigger_deg == &p1) ? &p2 : &p1;

    PolynomialNumber to_add, curr_memb;

    for(int i = 0; i <= DEG_P_N(*smaller_deg); i++){

        curr_memb = (*smaller_deg).get_member(i);

        to_add = MUL_PQ_P(*bigger_deg, curr_memb.get_coeff(i));
        to_add = MUL_Pxk_P(to_add, i);

        result = result + to_add;

    }

    return result;
}*/

PolynomialNumber Polinomial::DIV_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::MOD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::GCF_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::DER_P_P(const PolynomialNumber &p)
{
    return PolynomialNumber();
}

PolynomialNumber Polinomial::NMR_P_P(const PolynomialNumber &p)
{
    return PolynomialNumber();
}
