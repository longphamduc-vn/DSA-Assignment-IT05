// ==========================================
// File: utils/Validation.h
// Description: Các hàm hỗ trợ chuẩn hóa và bắt lỗi nhập liệu
// ==========================================
#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>

class Validation {
public:
    // 1. Xóa khoảng trắng thừa ở đầu và cuối chuỗi
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // 2. Chuẩn hóa Họ Tên (Viết hoa chữ cái đầu mỗi từ)
    static std::string normalizeName(std::string name) {
        name = trim(name);
        bool newWord = true;
        for (char& c : name) {
            if (std::isspace(c)) {
                newWord = true;
            } else if (newWord) {
                c = std::toupper(c);
                newWord = false;
            } else {
                c = std::tolower(c);
            }
        }
        return name;
    }

    // 3. Nhập số nguyên an toàn (Bảo vệ luồng cin không bị crash)
    static int getValidInteger(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "[Loi] Vui long nhap mot so nguyen hop le!\n";
                std::cin.clear(); // Xóa cờ lỗi
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Loại bỏ bộ đệm
            }
        }
    }

    // 4. Nhập số thực an toàn (Bảo vệ luồng cin)
    static double getValidDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "[Loi] Vui long nhap mot so thuc hop le!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    // 5. Kiểm tra định dạng ngày cơ bản (YYYY-MM-DD)
    static bool isValidDate(const std::string& date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;
        
        for (int i = 0; i < 10; i++) {
            if (i == 4 || i == 7) continue;
            if (!std::isdigit(date[i])) return false;
        }
        return true;
    }
};

#endif // VALIDATION_H