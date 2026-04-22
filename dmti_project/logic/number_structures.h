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

    QString toString(){
        QString res;
        for(int i = 0; i <= n; i++) res += QString::number(digits[i]);
        return res;
    }
};

#endif // NUMBER_STRUCTURES_H
