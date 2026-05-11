#ifndef NUMBER_STRUCTURES_H
#define NUMBER_STRUCTURES_H

#include <vector>
#include <qstring.h>
#include <QDebug>


struct Number{
    int n;
    std::vector<int> digits;

    Number(QString s){
        n = s.length() - 1;
        for(auto ch : s) digits.push_back(ch.digitValue());
    }

    Number(){
        n = 0;
        digits.push_back(0);
    }

    Number(const Number &other){
        n = other.n;
        digits = other.digits;
    }

    Number& operator=(const Number &other){
        if(this == &other) return *this;

        n = other.n;
        digits = other.digits;

        return *this;
    }

    QString toString() const{
        QString res;
        res.reserve(n + 1);
        for(int i = 0; i <= n; i++) res += QString::number(digits[i]);
        return res;
    }

    friend bool operator==(const Number &num1, const Number &num2){
        return num1.digits == num2.digits;
    }

    friend bool operator!=(const Number &num1, const Number &num2){
        return !(num1 == num2);
    }

    friend QDebug operator<<(QDebug dbg, const Number &num){
        QDebugStateSaver saver(dbg);
        dbg.nospace() << "Number(" << num.toString() << ")";
        return dbg;
    }
};

struct IntegerNumber{
    bool is_neg;
    int n;
    std::vector<int> digits;

    IntegerNumber(QString s){
        if (s[0] == '-'){
            is_neg = true;
            n = s.length() - 2;
        } else{
            is_neg = false;
            n = s.length() - 1;
        }
        for(auto ch : std::as_const(s)){
            if (ch.isDigit()){
                digits.push_back(ch.digitValue());
            }
        }
    }

    IntegerNumber(){
        is_neg = false;
        n = 0;
        digits.push_back(0);
    }

    QString toString() const{
        QString res;
        res.reserve(n + 2);
        if (is_neg){
            res += "-";
        }
        for(int i = 0; i <= n; i++) res += QString::number(digits[i]);
        return res;
    }

    friend bool operator==(const IntegerNumber &num1, const IntegerNumber &num2){
        return num1.digits == num2.digits && num1.is_neg == num2.is_neg;
    }

    friend bool operator!=(const IntegerNumber &num1, const IntegerNumber &num2){
        return !(num1 == num2);
    }

    friend QDebug operator<<(QDebug dbg, const IntegerNumber &num){
        QDebugStateSaver saver(dbg);
        dbg.nospace() << "IntegerNumber(" << num.toString() << ")";
        return dbg;
    }
};

struct RationalNumber {
    IntegerNumber numerator;
    Number denominator;

    RationalNumber(QString nStr, QString dStr) : numerator(nStr), denominator(dStr) {}
    RationalNumber(IntegerNumber num, Number den) : numerator(num), denominator(den) {}
    RationalNumber() = default;

    QString toString() const { return numerator.toString() + "/" + denominator.toString(); }

    friend bool operator==(const RationalNumber &a, const RationalNumber &b) {
        return a.numerator == b.numerator && a.denominator == b.denominator;
    }
    friend bool operator!=(const RationalNumber &a, const RationalNumber &b) { return !(a == b); }
    friend QDebug operator<<(QDebug dbg, const RationalNumber &r) {
        QDebugStateSaver saver(dbg);
        dbg.nospace() << "RationalNumber(" << r.toString() << ")"; return dbg;
    }
};

struct PolynomialNumber {
    int degree;
    std::vector<RationalNumber> coefficients;

    PolynomialNumber(int deg, std::vector<RationalNumber> coeffs)
        : degree(deg), coefficients(std::move(coeffs)) {}

    PolynomialNumber(int deg, RationalNumber coeff) : degree(deg) {
        coefficients.resize(deg + 1);
        coefficients[deg] = coeff;
    }

    PolynomialNumber() : degree(0) { coefficients.emplace_back(); }

    RationalNumber get_coeff(int deg) const {
        int index = degree - deg;
        if (index < 0 || index >= (int)coefficients.size()) return RationalNumber("0", "1");
        return coefficients[index];
    }

    QString toString() const {
        if (coefficients.empty()) return "0";
        QString res;
        for (int i = 0; i <= degree; ++i) {
            QString coeffStr = coefficients[i].toString();
            int power = degree - i;
            res += "(" + coeffStr + ")";
            if (power > 0) { res += "x^" + QString::number(power) + " + "; }
        }
        return res;
    }

    friend bool operator==(const PolynomialNumber &a, const PolynomialNumber &b) {
        if (a.degree != b.degree || a.coefficients.size() != b.coefficients.size()) return false;
        for (size_t i = 0; i < a.coefficients.size(); ++i)
            if (!(a.coefficients[i] == b.coefficients[i])) return false;
        return true;
    }
    friend bool operator!=(const PolynomialNumber &a, const PolynomialNumber &b) { return !(a == b); }
    friend QDebug operator<<(QDebug dbg, const PolynomialNumber &p) {
        QDebugStateSaver saver(dbg);
        dbg.nospace() << "PolynomialNumber(" << p.toString() << ")"; return dbg;
    }
};

#endif // NUMBER_STRUCTURES_H
