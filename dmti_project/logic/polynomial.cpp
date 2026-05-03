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

// P-2: SUB_PP_P — вычитание многочленов
PolynomialNumber Polynomial::SUB_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2) {
    int max_deg = std::max(p1.degree, p2.degree);

    PolynomialNumber result;
    result.degree = max_deg;
    result.coefficients.clear();
    result.coefficients.resize(max_deg + 1);

    for (int i = 0; i <= max_deg; ++i) {
        result.coefficients[i] = SUB_QQ_Q(p1.get_coeff(i), p2.get_coeff(i));
    }

    while (result.degree > 0) {
        const RationalNumber &lead = result.coefficients[result.degree];
        if (lead.numerator.n == 0 && lead.numerator.digits.size() == 1 && lead.numerator.digits[0] == 0) {
            result.coefficients.pop_back();
            result.degree--;
        } else {
            break;
        }
    }

    return result;
}

// P-11: GCF_PP_P — НОД многочленов (алгоритм Евклида)
PolynomialNumber Polynomial::GCF_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2) {
    PolynomialNumber a = p1;
    PolynomialNumber b = p2;

    auto isZeroPoly = [](const PolynomialNumber &p) -> bool {
        for (const auto &c : p.coefficients) {
            if (!(c.numerator.n == 0 && c.numerator.digits.size() == 1 && c.numerator.digits[0] == 0))
                return false;
        }
        return true;
    };

    while (!isZeroPoly(b)) {
        PolynomialNumber temp = MOD_PP_P(a, b);
        a = b;
        b = temp;
        b.degree = DEG_P_N(b);
    }
    return a;
}