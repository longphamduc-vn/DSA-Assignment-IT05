// ==========================================
// File: data/FileIO.h
// Description: Utility class for File Input/Output operations
// ==========================================
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../core/LinkedList.h"
#include "../models/Tour.h"
#include "../models/Customer.h"
#include "../models/Employee.h"
#include "../models/Booking.h"

class FileIO {
public:
    template <typename T>
    static void saveList(const std::string& filename, const LinkedList<T>& list) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        Node<T>* current = list.getHead();
        while (current != nullptr) {
            file << current->data.toFileString() << "\n";
            current = current->next;
        }
    }

    template <typename T>
    static void loadList(const std::string& filename, LinkedList<T>& list) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            T item;
            item.fromFileString(line);
            list.insert(std::move(item), INSERT_TAIL);
        }
    }
};

#endif