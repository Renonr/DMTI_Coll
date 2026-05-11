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

    for (int power = 0; power <= max_deg; power++) {
        int idx = max_deg - power;
        result.coefficients[idx] = ADD_QQ_Q(p1.get_coeff(power), p2.get_coeff(power));
    }

    while (result.degree > 0 && !result.coefficients.empty() &&
           result.coefficients[0].numerator.toString() == "0") {
        result.coefficients.erase(result.coefficients.begin());
        result.degree--;
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

    for (int power = 0; power <= max_deg; power++) {
        int idx = max_deg - power;
        result.coefficients[idx] = SUB_QQ_Q(p1.get_coeff(power), p2.get_coeff(power));
    }

    while (result.degree > 0 && !result.coefficients.empty() &&
           result.coefficients[0].numerator.toString() == "0") {
        result.coefficients.erase(result.coefficients.begin());
        result.degree--;
    }

    return result;
}

// #35 P-3
// Умножение многочлена на рациональное число
// Сериков Владислав 5387
PolynomialNumber Polinomial::MUL_PQ_P(const PolynomialNumber &p, const RationalNumber &q)
{
    PolynomialNumber result = p;

    for(int i = 0; i <= result.degree; i++){
        result.coefficients[i] = MUL_QQ_Q(result.coefficients[i], q);
    }

    return result;
}

// #36 P-4
// Умножение многочлена на x^k
// Вековищев Кирилл 5387
PolynomialNumber Polinomial::MUL_Pxk_P(const PolynomialNumber &p, int k)
{
    if (k <= 0) return p;

    PolynomialNumber result;
    result.degree = p.degree + k;
    result.coefficients = p.coefficients;
    result.coefficients.insert(result.coefficients.end(), k, RationalNumber("0", "1"));

    return result;
}

// #37 P-5
// Старший коэффициент многочлена
// Ковалев Иван 5387
RationalNumber Polinomial::LED_P_Q(const PolynomialNumber &p)
{
    return p.get_coeff(p.degree);
}

// #38 P-6
// Степень многочлена
// Клочкова Лидия 5387
Number Polinomial::DEG_P_N(const PolynomialNumber &p) {
    if (p.coefficients.empty()) {
        return Number("0");
    }

    for (int i = 0; i < (int)p.coefficients.size(); i++) {
        const RationalNumber &coef = p.coefficients[i];

        if (coef.numerator.toString() != "0") {
            int actual_degree = p.degree - i;
            return Number(QString::number(actual_degree));
        }
    }

    return Number("0");
}

// #39 P-7
// Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей
// Палешева Ариадна 5387
RationalNumber Polinomial::FAC_P_Q(const PolynomialNumber &p)
{
    if (p.coefficients.empty()) {
        return RationalNumber("0", "1");
    }

    Number lcm_denoms = p.coefficients[0].denominator;

    Number gcd_nums = ABS_Z_N(p.coefficients[0].numerator);

    for (size_t i = 1; i < p.coefficients.size(); i++) {
        const RationalNumber &coeff = p.coefficients[i];
        Number denom = coeff.denominator;
        Number gcd_denoms = GCF_NN_N(lcm_denoms, denom);
        lcm_denoms = DIV_NN_N(MUL_NN_N(lcm_denoms, denom), gcd_denoms);

        Number num_abs = ABS_Z_N(coeff.numerator);
        gcd_nums = GCF_NN_N(gcd_nums, num_abs);
    }

    IntegerNumber gcd_int = TRANS_N_Z(gcd_nums);
    return RationalNumber(gcd_int, lcm_denoms);
}

// #40 P-8
// Умножение многочленов
// Кушаев Дмитрий 5387
PolynomialNumber Polinomial::MUL_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2){
    int deg1 = p1.degree;
    int deg2 = p2.degree;
    int result_deg = deg1 + deg2;

    std::vector<RationalNumber> result_coeffs(result_deg + 1, RationalNumber("0", "1"));

    for (int i = 0; i <= deg1; i++) {
        for (int j = 0; j <= deg2; j++) {
            RationalNumber prod = MUL_QQ_Q(p1.coefficients[i], p2.coefficients[j]);

            int target_deg = (deg1 - i) + (deg2 - j);

            int idx = result_deg - target_deg;

            result_coeffs[idx] = ADD_QQ_Q(result_coeffs[idx], prod);
        }
    }

    PolynomialNumber result(result_deg, result_coeffs);

    while (result.degree > 0 && !result.coefficients.empty() &&
           result.coefficients[0].numerator.toString() == "0") {
        result.coefficients.erase(result.coefficients.begin());
        result.degree--;
    }

    return result;
}

// #41 P-9
// Частное от деления многочлена на многочлен при делении с остатком
// Грачева Елизавета 5387
PolynomialNumber Polinomial::DIV_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    auto isZeroPoly = [](const PolynomialNumber &p) -> bool {
        for (const auto &c : p.coefficients) {
            if (c.numerator.toString() != "0")
                return false;
        }
        return true;
    };

    if (isZeroPoly(p2)) {
        throw std::runtime_error("На ноль делить нельзя!");
    }

    int deg_dividend = p1.degree;
    int deg_divisor = p2.degree;

    if (deg_dividend < deg_divisor) {
        return PolynomialNumber();
    }

    PolynomialNumber remainder = p1;
    PolynomialNumber quotient;
    quotient.degree = 0;
    quotient.coefficients = {RationalNumber("0", "1")};

    int max_iter = deg_dividend - deg_divisor + 10;
    int iter = 0;

    while (iter < max_iter) {
        iter++;

        int rem_deg = remainder.degree;
        int div_deg = deg_divisor;

        if (rem_deg < div_deg) {
            break;
        }

        if (isZeroPoly(remainder)) {
            break;
        }

        RationalNumber lead_coeff_rem = remainder.coefficients[0];
        RationalNumber lead_coeff_div = p2.coefficients[0];


        if (lead_coeff_div.numerator.toString() == "0") {
            throw std::runtime_error("Division by zero coefficient!");
        }

        RationalNumber q_coeff = DIV_QQ_Q(lead_coeff_rem, lead_coeff_div);
        int term_deg = rem_deg - div_deg;

        PolynomialNumber term;
        term.degree = term_deg;
        term.coefficients.resize(term_deg + 1, RationalNumber("0", "1"));
        term.coefficients[0] = q_coeff;

        quotient = ADD_PP_P(quotient, term);

        PolynomialNumber product = MUL_PP_P(term, p2);

        remainder = SUB_PP_P(remainder, product);

        remainder.degree = remainder.degree;

        int new_deg = -1;
        for (int i = 0; i < (int)remainder.coefficients.size(); i++) {
            if (remainder.coefficients[i].numerator.toString() != "0") {
                new_deg = remainder.degree - i;
                break;
            }
        }
        if (new_deg >= 0) {
            remainder.degree = new_deg;
        } else {
            remainder.degree = 0;
        }

    }

    while (quotient.degree > 0 && !quotient.coefficients.empty()) {
        if (quotient.coefficients[0].numerator.toString() == "0") {
            quotient.coefficients.erase(quotient.coefficients.begin());
            quotient.degree--;
        } else {
            break;
        }
    }

    if (quotient.coefficients.empty()) {
        return PolynomialNumber();
    }

    return quotient;
}

// #42 P-10
// Остаток от деления многочлена на многочлен при делении с остатком
// Баданюк Валерий 5387
PolynomialNumber Polinomial::MOD_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    auto isZeroPoly = [](const PolynomialNumber &p) -> bool {
        for (const auto &c : p.coefficients) {
            if (c.numerator.toString() != "0")
                return false;
        }
        return true;
    };

    if (isZeroPoly(p2)) {
        throw std::runtime_error("На ноль делить нельзя!");
    }

    PolynomialNumber q = DIV_PP_P(p1, p2);

    PolynomialNumber product = MUL_PP_P(q, p2);

    PolynomialNumber r = SUB_PP_P(p1, product);

    r.degree = DEG_P_N(r).toString().toInt();

    while (r.degree > 0 && !r.coefficients.empty()) {
        if (r.coefficients[0].numerator.toString() == "0") {
            r.coefficients.erase(r.coefficients.begin());
            r.degree--;
        } else {
            break;
        }
    }

    if (r.coefficients.empty()) {
        return PolynomialNumber();
    }

    return r;
}

// #43 P-11
// НОД многочленов
// Степанов Леонид 5387
PolynomialNumber Polinomial::GCF_PP_P(const PolynomialNumber &p1, const PolynomialNumber &p2)
{
    auto isZeroPoly = [](const PolynomialNumber &p) -> bool {
        for (const auto &c : p.coefficients) {
            if (c.numerator.toString() != "0")
                return false;
        }
        return true;
    };

    if (isZeroPoly(p1) && isZeroPoly(p2)) {
        return PolynomialNumber();
    }
    if (isZeroPoly(p1)) {
        return p2;
    }
    if (isZeroPoly(p2)) {
        return p1;
    }

    PolynomialNumber a = p1;
    PolynomialNumber b = p2;

    while (!isZeroPoly(b)) {
        PolynomialNumber r = MOD_PP_P(a, b);

        a = b;
        b = r;

        a.degree = DEG_P_N(a).toString().toInt();
        b.degree = DEG_P_N(b).toString().toInt();
    }

    if (a.degree >= 0 && !a.coefficients.empty() && !isZeroPoly(a)) {
        RationalNumber lead_coeff = a.coefficients[0];

        if (lead_coeff.numerator.toString() != "1" || lead_coeff.denominator.toString() != "1") {
            for (auto &coeff : a.coefficients) {
                coeff = DIV_QQ_Q(coeff, lead_coeff);
            }
        }

        if (a.coefficients[0].numerator.is_neg) {
            for (auto &coeff : a.coefficients) {
                coeff.numerator = MUL_ZM_Z(coeff.numerator);
            }
        }
    }

    return a;
}

// #44 P-12
// Производная многочлена
// Сериков Владислав 5387
PolynomialNumber Polinomial::DER_P_P(const PolynomialNumber &p)
{
    if (p.degree == 0) {
        return PolynomialNumber(0, {RationalNumber("0", "1")});
    }

    std::vector<RationalNumber> result_coeffs;

    for (int i = 0; i < p.degree; i++) {
        int power = p.degree - i;
        RationalNumber power_num(QString::number(power), "1");
        result_coeffs.push_back(MUL_QQ_Q(p.coefficients[i], power_num));
    }

    return PolynomialNumber(p.degree - 1, result_coeffs);
}

// #45 P-13
// Преобразование многочлена (кратные корни в простые)
// Вековищев Кирилл 5387
PolynomialNumber Polinomial::NMR_P_P(const PolynomialNumber &p)
{
    auto isZeroPoly = [](const PolynomialNumber &poly) -> bool {
        for (const auto &c : poly.coefficients) {
            if (c.numerator.toString() != "0")
                return false;
        }
        return true;
    };

    int deg = DEG_P_N(p).toString().toInt();
    if (deg <= 0) {
        return p;
    }

    PolynomialNumber derivative = DER_P_P(p);

    if (isZeroPoly(derivative)) {
        return p;
    }

    PolynomialNumber gcf = GCF_PP_P(p, derivative);

    int gcf_deg = DEG_P_N(gcf).toString().toInt();
    if (gcf_deg == 0) {
        return p;
    }

    PolynomialNumber result = DIV_PP_P(p, gcf);

    return result;
}
