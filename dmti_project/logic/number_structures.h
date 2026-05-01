#ifndef NUMBER_STRUCTURES_H
#define NUMBER_STRUCTURES_H

#include <vector>
#include <qstring.h>

struct Number{
    int n;
    std::vector<int> digits;

    Number(QString s){
        n = s.length() - 1;
        for(auto ch : s) digits.push_back(ch.digitValue());
    }

    QString toString() const{
        QString res;
        res.reserve(n + 1);
        for(int i = 0; i <= n; i++) res += QString::number(digits[i]);
        return res;
    }
};

struct IntegerNumber{
    bool sign;
    int n;
    std::vector<int> digits;

    IntegerNumber(QString s){
        if (s[0] == '-'){
            sign = true;
            n = s.length() - 2;
        } else{
            sign = false;
            n = s.length() - 1;
        }
        for(auto ch : std::as_const(s)){
            if (ch.isDigit()){
                digits.push_back(ch.digitValue());
            }
        }
    }

    QString toString() const{
        QString res;
        res.reserve(n + 2);
        if (sign){
            res += "-";
        }
        for(int i = 0; i <= n; i++) res += QString::number(digits[i]);
        return res;
    }
};

struct RationalNumber {
    IntegerNumber numerator;
    Number denominator;

    RationalNumber(QString nStr, QString dStr)
        : numerator(nStr), denominator(dStr) {}

    QString toString() const {
        return numerator.toString() + "/" + denominator.toString();
    }
};

struct Polynomial {
    int m;
    std::vector<RationalNumber> coefficients;

    Polynomial(int degree, std::vector<RationalNumber> coeffs)
        : m(degree), coefficients(coeffs) {}

    QString toString() const {
        if (coefficients.empty()) return "0";

        QString res;
        for (int i = 0; i <= m; ++i) {
            QString coeffStr = coefficients[i].toString();
            int power = m - i;

            res += "(" + coeffStr + ")";

            if (power > 0) {
                res += "x^" + QString::number(power);
                res += " + ";
            }
        }
        return res;
    }
};

#endif // NUMBER_STRUCTURES_H
