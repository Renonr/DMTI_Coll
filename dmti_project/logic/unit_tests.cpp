#include "number_structures.h"

#include "natural.h"
#include "integer.h"
#include "rational.h"
#include "polinomial.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

// NATURAL
// ниже юнит-тесты для натуральных чисел (NATURAL)

// функция для сравнения результатов
bool areEqual(const Number& res, const std::vector<int>& expected) {
    return res.digits == expected;
}

// функция для вывода вектора (чтобы видеть ошибку, если тест не прошел)
void printDigits(const std::vector<int>& v) {
    for (int d : v) std::cout << d;
}

void run_tests() {
    {
        Number n1; n1.digits = {1, 2}; n1.n = 2;
        Number n2; n2.digits = {3, 4}; n2.n = 2;
        Number res = Natural::ADD_NN_N(n1, n2);
        
        assert(areEqual(res, {4, 6}));
        std::cout << "Test 1 Passed: 12 + 34 = 46" << std::endl;
    }

    {
        Number n1; n1.digits = {9}; n1.n = 1;
        Number n2; n2.digits = {1}; n2.n = 1;
        Number res = Natural::ADD_NN_N(n1, n2);
        
        assert(areEqual(res, {1, 0}));
        std::cout << "Test 2 Passed: 9 + 1 = 10" << std::endl;
    }

    {
        Number n1; n1.digits = {1, 0, 0}; n1.n = 3;
        Number n2; n2.digits = {1};       n2.n = 1;
        Number res = Natural::ADD_NN_N(n1, n2);
        
        assert(areEqual(res, {1, 0, 1}));
        std::cout << "Test 3 Passed: 100 + 1 = 101" << std::endl;
    }

    {
        Number n1; n1.digits = {9, 9, 9}; n1.n = 3;
        Number n2; n2.digits = {1};       n2.n = 1;
        Number res = Natural::ADD_NN_N(n1, n2);
        
        assert(areEqual(res, {1, 0, 0, 0}));
        std::cout << "Test 4 Passed: 999 + 1 = 1000" << std::endl;
    }

    std::cout << "\nALL TESTS PASSED!" << std::endl;
}

// INTEGER
// ниже юнит-тесты для целых чисел (INTEGER)

// RATIONAL
// ниже юнит-тесты для рациональных чисел (RATIONAL)

// POLYNOMIAL
// ниже юнит-тесты для многочленов