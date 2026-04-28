#pragma once
#include <iostream>
#include <string>

class Validator {
public:
    static void clearInputBuffer();

    static bool isPositiveInteger(const std::string& str);

    static bool isPositive(double number);
};