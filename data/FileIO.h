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
    // ==========================================
    // 1. Quản lý File Tour
    // ==========================================
    static void saveTours(const std::string& filename, const LinkedList<Tour>& list) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        Node<Tour>* current = list.getHead();
        while (current != nullptr) {
            const Tour& t = current->data;
            file << t.tourId << "|" << t.destination << "|" 
                 << t.price << "|" << t.maxCapacity << "|" 
                 << t.availableSeats << "|" << t.departureDate << "|" 
                 << t.status << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadTours(const std::string& filename, LinkedList<Tour>& list) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string id, dest, date, status, temp;
            double price = 0;
            int maxCap = 0, avail = 0;

            std::getline(ss, id, '|');
            std::getline(ss, dest, '|');
            
            if (std::getline(ss, temp, '|')) price = std::stod(temp);
            if (std::getline(ss, temp, '|')) maxCap = std::stoi(temp);
            if (std::getline(ss, temp, '|')) avail = std::stoi(temp);
            
            std::getline(ss, date, '|');
            std::getline(ss, status, '|');

            Tour t(id, dest, price, maxCap, date);
            t.availableSeats = avail;
            t.status = status;
            list.addLast(t);
        }
        file.close();
    }

    // ==========================================
    // 2. Quản lý File Customer
    // ==========================================
    static void saveCustomers(const std::string& filename, const LinkedList<Customer>& list) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        Node<Customer>* current = list.getHead();
        while (current != nullptr) {
            const Customer& c = current->data;
            file << c.customerId << "|" << c.fullName << "|" 
                 << c.phoneNumber << "|" << c.email << "|" 
                 << c.address << "|" << c.totalSpent << "|" 
                 << (c.isDeleted ? "1" : "0") << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadCustomers(const std::string& filename, LinkedList<Customer>& list) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string id, name, phone, email, addr, temp;
            double spent = 0;
            bool deleted = false;

            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, phone, '|');
            std::getline(ss, email, '|');
            std::getline(ss, addr, '|');
            
            if (std::getline(ss, temp, '|')) spent = std::stod(temp);
            if (std::getline(ss, temp, '|')) deleted = (temp == "1");

            Customer c(id, name, phone, email, addr);
            c.totalSpent = spent;
            c.isDeleted = deleted;
            list.addLast(c);
        }
        file.close();
    }

    // ==========================================
    // 3. Quản lý File Employee
    // ==========================================
    static void saveEmployees(const std::string& filename, const LinkedList<Employee>& list) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        Node<Employee>* current = list.getHead();
        while (current != nullptr) {
            const Employee& e = current->data;
            file << e.employeeId << "|" << e.fullName << "|" 
                 << e.position << "|" << e.bookingCount << "|" 
                 << e.totalSales << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadEmployees(const std::string& filename, LinkedList<Employee>& list) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string id, name, pos, temp;
            int count = 0;
            double sales = 0;

            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, pos, '|');
            
            if (std::getline(ss, temp, '|')) count = std::stoi(temp);
            if (std::getline(ss, temp, '|')) sales = std::stod(temp);

            Employee e(id, name, pos);
            e.bookingCount = count;
            e.totalSales = sales;
            list.addLast(e);
        }
        file.close();
    }

    // ==========================================
    // 4. Quản lý File Booking (Nested List serialization)
    // ==========================================
    static void saveBookings(const std::string& filename, const LinkedList<Booking>& list) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        Node<Booking>* current = list.getHead();
        while (current != nullptr) {
            const Booking& b = current->data;
            file << b.bookingId << "|" << b.customerId << "|" 
                 << b.tourId << "|" << b.employeeId << "|" 
                 << b.passengerCount << "|" << b.totalAmount << "|" 
                 << b.bookingDate << "|" << b.status << "|";
            
            // Lưu nested list hành khách: Ten1,ID1;Ten2,ID2;
            Node<Passenger>* pNode = b.passengers.getHead();
            while (pNode != nullptr) {
                file << pNode->data.name << "," << pNode->data.idCard << ";";
                pNode = pNode->next;
            }
            file << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadBookings(const std::string& filename, LinkedList<Booking>& list) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string bId, cId, tId, eId, date, status, temp, passengersData;
            int pCount = 0;
            double amount = 0;

            std::getline(ss, bId, '|');
            std::getline(ss, cId, '|');
            std::getline(ss, tId, '|');
            std::getline(ss, eId, '|');
            
            if (std::getline(ss, temp, '|')) pCount = std::stoi(temp);
            if (std::getline(ss, temp, '|')) amount = std::stod(temp);
            
            std::getline(ss, date, '|');
            std::getline(ss, status, '|');
            std::getline(ss, passengersData, '|');

            Booking b(bId, cId, tId, eId, date);
            b.passengerCount = pCount;
            b.totalAmount = amount;
            b.status = status;

            // Phân tích cú pháp nested list hành khách
            if (!passengersData.empty()) {
                std::stringstream pss(passengersData);
                std::string pToken;
                while (std::getline(pss, pToken, ';')) {
                    if (pToken.empty()) continue;
                    std::stringstream detail(pToken);
                    std::string pName, pIdCard;
                    std::getline(detail, pName, ',');
                    std::getline(detail, pIdCard, ',');
                    b.passengers.addLast(Passenger(pName, pIdCard));
                }
            }
            list.addLast(b);
        }
        file.close();
    }
};

#endif // FILE_IO_H