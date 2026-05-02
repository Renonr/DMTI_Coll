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

    // конструктор по умолчанию; создаёт ноль
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
};

struct RationalNumber {
    IntegerNumber numerator;
    Number denominator;

    RationalNumber(QString nStr, QString dStr)
        : numerator(nStr), denominator(dStr) {}

    RationalNumber(){}

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
