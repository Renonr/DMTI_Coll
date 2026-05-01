#ifndef POLINOMIAL_H
#define POLINOMIAL_H

#include "number_structures.h"
#include "rational.h"

class Polinomial : public Rational
{
public:
    Polinomial();

    PolynomialNumber ADD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    PolynomialNumber SUB_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    PolynomialNumber MUL_PQ_P(const PolynomialNumber &p, const RationalNumber &q);

    PolynomialNumber MUL_Pxk_P(const PolynomialNumber &p, int k);

    RationalNumber LED_P_Q(const PolynomialNumber &p);

    Number DEG_P_N(const PolynomialNumber &p);

    RationalNumber FAC_P_Q(const PolynomialNumber &p);

    PolynomialNumber MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    PolynomialNumber DIV_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    PolynomialNumber MOD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    PolynomialNumber GCF_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    PolynomialNumber DER_P_P(const PolynomialNumber &p);

    PolynomialNumber NMR_P_P(const PolynomialNumber &p);
};

#endif // POLINOMIAL_H
