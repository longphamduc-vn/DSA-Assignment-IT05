// ==========================================
// File: utils/ConsoleUI.h
// Description: Giao diện hiển thị bảng và tiện ích Console
// ==========================================
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <iostream>
#include <iomanip>
#include <string>
#include "../core/LinkedList.h"
#include "../models/Tour.h"
#include "../models/Customer.h"
#include "../models/Booking.h"

class ConsoleUI {
public:
    static void clearScreen() {

        #if defined(_WIN32)
            system("cls");
        #else
            system("clear");
        #endif
    }

    static void pauseScreen() {
        std::cout << "\nNhan Enter de tiep tuc...";
        std::cin.get();
    }

    static void printLine(int length = 80, char ch = '-') {
        std::cout << std::string(length, ch) << "\n";
    }

    // ==========================================
    // 2. Các hàm vẽ bảng dữ liệu
    // ==========================================
    
    // In danh sách Tour
    static void printTourTable(const LinkedList<Tour>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Danh sach Tour hien tai dang trong.\n";
            return;
        }

        printLine(85, '=');
        std::cout << std::left << std::setw(8) << "ID" 
                  << std::setw(20) << "Diem den" 
                  << std::setw(15) << "Gia (VND)" 
                  << std::setw(12) << "Tong cho" 
                  << std::setw(10) << "Con trong" 
                  << std::setw(12) << "Ngay KH" 
                  << std::setw(10) << "Trang thai" << "\n";
        printLine(85, '-');

        Node<Tour>* current = list.getHead();
        while (current != nullptr) {
            const Tour& t = current->data;
            std::cout << std::left << std::setw(8) << t.tourId
                      << std::setw(20) << t.destination
                      << std::setw(15) << std::fixed << std::setprecision(0) << t.price
                      << std::setw(12) << t.maxCapacity
                      << std::setw(10) << t.availableSeats
                      << std::setw(12) << t.departureDate
                      << std::setw(10) << t.status << "\n";
            current = current->next;
        }
        printLine(85, '=');
    }

    // In danh sách Khách hàng
    static void printCustomerTable(const LinkedList<Customer>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Danh sach Khach hang hien tai dang trong.\n";
            return;
        }

        printLine(85, '=');
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(25) << "Ho va Ten" 
                  << std::setw(15) << "So dien thoai" 
                  << std::setw(20) << "Tong chi tieu" 
                  << std::setw(15) << "Trang thai" << "\n";
        printLine(85, '-');

        Node<Customer>* current = list.getHead();
        while (current != nullptr) {
            const Customer& c = current->data;
            std::cout << std::left << std::setw(10) << c.customerId
                      << std::setw(25) << c.fullName
                      << std::setw(15) << c.phoneNumber
                      << std::setw(20) << std::fixed << std::setprecision(0) << c.totalSpent
                      << std::setw(15) << (c.isDeleted ? "[Da xoa]" : "Hoat dong") << "\n";
            current = current->next;
        }
        printLine(85, '=');
    }

    // In danh sách Booking
    static void printBookingTable(const LinkedList<Booking>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Khong co du lieu Booking.\n";
            return;
        }

        printLine(90, '=');
        std::cout << std::left << std::setw(10) << "Book ID" 
                  << std::setw(10) << "Khach ID" 
                  << std::setw(10) << "Tour ID" 
                  << std::setw(10) << "So khach" 
                  << std::setw(15) << "Tong tien" 
                  << std::setw(15) << "Ngay dat" 
                  << std::setw(15) << "Trang thai" << "\n";
        printLine(90, '-');

        Node<Booking>* current = list.getHead();
        while (current != nullptr) {
            const Booking& b = current->data;
            std::cout << std::left << std::setw(10) << b.bookingId
                      << std::setw(10) << b.customerId
                      << std::setw(10) << b.tourId
                      << std::setw(10) << b.passengerCount
                      << std::setw(15) << std::fixed << std::setprecision(0) << b.totalAmount
                      << std::setw(15) << b.bookingDate
                      << std::setw(15) << b.status << "\n";
            current = current->next;
        }
        printLine(90, '=');
    }
};

#endif // CONSOLE_UI_H