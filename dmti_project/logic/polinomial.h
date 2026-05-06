#ifndef POLINOMIAL_H
#define POLINOMIAL_H

#include "number_structures.h"
#include "rational.h"

class Polinomial : public Rational
{
public:
    Polinomial();

    static PolynomialNumber ADD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    static PolynomialNumber SUB_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    static PolynomialNumber MUL_PQ_P(const PolynomialNumber &p, const RationalNumber &q);

    static PolynomialNumber MUL_Pxk_P(const PolynomialNumber &p, const Number &k);

    static RationalNumber LED_P_Q(const PolynomialNumber &p);

    static Number DEG_P_N(const PolynomialNumber &p);

    static RationalNumber FAC_P_Q(const PolynomialNumber &p);

    static PolynomialNumber MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    static PolynomialNumber DIV_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    static PolynomialNumber MOD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    static PolynomialNumber GCF_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2);

    static PolynomialNumber DER_P_P(const PolynomialNumber &p);

    static PolynomialNumber NMR_P_P(const PolynomialNumber &p);
};

#endif // POLINOMIAL_H
