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

void run_SUB_ND_N(){
    {
        Number n1; n1.digits = {4, 8}; n1.n = 1;
        Number n2; n2.digits = {1, 2}; n2.n = 1;
        int digit = 2;
        Number res = Natural::SUB_NDN_N(n1, n2, digit);
        assert(areEqual(res, {2, 4}));
        std::cout << "Test SUB_ND_N Passed: 48 - 12*2 = 24" << std::endl;
    }

    {
        Number n1; n1.digits = {1, 0, 0}; n1.n = 2;
        Number n2; n2.digits = {2, 5}; n2.n = 1;
        int digit = 4;
        Number res = Natural::SUB_NDN_N(n1, n2, digit);
        assert(areEqual(res, {0}));
        std::cout << "Test SUB_ND_N Passed: 100 - 25*4 = 0" << std::endl;
    }

    {
        Number n1; n1.digits = {1, 0, 0, 0}; n1.n = 3;
        Number n2; n2.digits = {1, 5, 0}; n2.n = 2;
        int digit = 8;
        bool exception = false;
    try {
        Natural::SUB_NDN_N(n1, n2, digit);
    } catch (const std::invalid_argument& e) {
        exception = true;
        
        assert(std::string(e.what()) == "num1 < num2 * digit");
        std::cout << "Test Passed: num1 < num2 * digit" << std::endl;
    }

    assert(exception);
    } 
}

// INTEGER
// ниже юнит-тесты для целых чисел (INTEGER)

// RATIONAL
// ниже юнит-тесты для рациональных чисел (RATIONAL)

// POLYNOMIAL
// ниже юнит-тесты для многочленов