#include "polinomial.h"

Polinomial::Polinomial() {}

// #33 P-1
// Сложение многочленов
// Баданюк Валерий 5387
PolynomialNumber Polinomial::ADD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2) {
    int max_deg = std::max(p1.degree, p2.degree);

    PolynomialNumber result;
    result.degree = max_deg;
    result.coefficients.clear();
    result.coefficients.resize(max_deg + 1);

    for (int i = 0; i <= max_deg; i++) {
        result.coefficients[i] = ADD_QQ_Q(p1.get_coeff(i), p2.get_coeff(i));
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

// #34 P-2
// Вычитание многочленов
// Степанов Леонид 5387
PolynomialNumber Polinomial::SUB_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2) {
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

// #35 P-3
// Умножение многочлена на рациональное число
// Сериков Владислав 5387
PolynomialNumber Polinomial::MUL_PQ_P(const PolynomialNumber &p, const RationalNumber &q)
{
    return PolynomialNumber();
}

// #36 P-4
// Умножение многочлена на x^k
// Вековищев Кирилл 5387
PolynomialNumber Polinomial::MUL_Pxk_P(const PolynomialNumber &p, const Number &k)
{
    return PolynomialNumber();
}

// #37 P-5
// Старший коэффициент многочлена
// Ковалев Иван 5387
RationalNumber Polinomial::LED_P_Q(const PolynomialNumber &p)
{
    return RationalNumber();
}

// #38 P-6
// Степень многочлена
// Клочкова Лидия 5387 
Number Polinomial::DEG_P_N(const PolynomialNumber &p)
{
    return Number();
}

// #39 P-7
// Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей
// Палешева Ариадна 5387
RationalNumber Polinomial::FAC_P_Q(const PolynomialNumber &p)
{
    return RationalNumber();
}

// #40 P-8
// Умножение многочленов
// Кушаев Дмитрий 5387
PolynomialNumber Polinomial::MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2){

    PolynomialNumber result;

    result.degree = DEG_P_N(p1).n + DEG_P_N(p2).n;

    const PolynomialNumber *bigger_deg = (DEG_P_N(p1).n > DEG_P_N(p2).n) ? &p1 : &p2;
    const PolynomialNumber *smaller_deg = (bigger_deg == &p1) ? &p2 : &p1;

    PolynomialNumber to_add, curr_memb;

    for(int i = 0; i <= DEG_P_N(*smaller_deg).n; i++){

        curr_memb = (*smaller_deg).get_member(i);

        to_add = MUL_PQ_P(*bigger_deg, curr_memb.get_coeff(i));
        to_add = MUL_Pxk_P(to_add, Number(QString::number(i)));

        result.degree = result.degree + to_add.degree;
    }

    return result;
}

// #41 P-9
// Частное от деления многочлена на многочлен при делении с остатком
// Грачева Елизавета 5387
PolynomialNumber Polinomial::DIV_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    return PolynomialNumber();
}

// #42 P-10
// Остаток от деления многочлена на многочлен при делении с остатком
// Баданюк Валерий 5387
PolynomialNumber Polinomial::MOD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    PolynomialNumber q = DIV_PP_P(p1, p2);
    PolynomialNumber r = SUB_PP_P(p1, MUL_PP_P(q, p2));
    // p1 = p2*q + r
    // r = p1 - p2*q

    return r;
}

// #43 P-11
// НОД многочленов
// Степанов Леонид 5387
PolynomialNumber Polinomial::GCF_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2) {
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
        b.degree = DEG_P_N(b).n;
    }
    return a;
}

// #44 P-12
// Производная многочлена
// Сериков Владислав 5387
PolynomialNumber Polinomial::DER_P_P(const PolynomialNumber &p)
{
    return PolynomialNumber();
}

// #45 P-13
// Преобразование многочлена (кратные корни в простые)
// Вековищев Кирилл 5387
PolynomialNumber Polinomial::NMR_P_P(const PolynomialNumber &p)
{
    return PolynomialNumber();
}
