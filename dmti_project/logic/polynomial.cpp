#include "polynomial.h"

Polynomial::Polynomial() {}

PolynomialNumber Polynomial::MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2){

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
}