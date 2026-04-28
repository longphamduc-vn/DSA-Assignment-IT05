#include "FileHandler.h"

bool FileHandler::fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good(); 
}

void FileHandler::clearFile(const std::string& filePath) {
    std::ofstream file(filePath, std::ios::trunc);
    if (file.is_open()) {
        file.close();
    }
}

void FileHandler::appendLine(const std::string& filePath, const std::string& line) {
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open()) {
        file << line << "\n";
        file.close();
    } else {
        std::cerr << "Loi: Khong the mo file " << filePath << " de ghi.\n";
    }
}