#include "Validator.h"
#include <limits>
#include <cctype> // Chứa hàm isdigit

void Validator::clearInputBuffer() {
    if (std::cin.fail()) {
        std::cin.clear(); 
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Validator::isPositiveInteger(const std::string& str) {
    if (str.empty()) return false;
    
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool Validator::isPositive(double number) {
    return number > 0;
}