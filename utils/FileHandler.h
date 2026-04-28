#pragma once
#include <string>
#include <fstream>
#include <iostream>

class FileHandler {
public:
    static bool fileExists(const std::string& filePath);

    static void clearFile(const std::string& filePath);

    static void appendLine(const std::string& filePath, const std::string& line);
};