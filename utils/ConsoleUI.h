// ==========================================
// File: utils/ConsoleUI.h
// Description: Giao diện hiển thị bảng, nhập liệu và tiện ích Console
// ==========================================
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits> // Thêm thư viện này để dùng numeric_limits cho cin.ignore()
#include "../core/LinkedList.h"
#include "../models/Tour.h"
#include "../models/Customer.h"
#include "../models/Booking.h"

class ConsoleUI {
public:
    // ==========================================
    // 1. Các tiện ích màn hình
    // ==========================================
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

    static void printEmployeeTable(const LinkedList<Employee>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Danh sach Nhan vien hien tai dang trong.\n";
            return;
        }

        printLine(50, '=');
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(25) << "Ho va Ten" 
                  << std::setw(15) << "Chuc vu" << "\n";
        printLine(50, '-');

        Node<Employee>* current = list.getHead();
        while (current != nullptr) {
            const Employee& e = current->data;
            std::cout << std::left << std::setw(10) << e.employeeId
                      << std::setw(25) << e.fullName
                      << std::setw(15) << e.position << "\n";
            current = current->next;
        }
        printLine(50, '=');
    }
    // ==========================================
    // 2. Các hàm vẽ bảng dữ liệu (Output)
    // ==========================================
    
    // In danh sách Tour
    static void printTourTable(const LinkedList<Tour>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Danh sach Tour hien tai dang trong.\n";
            return;
        }

        printLine(63, '=');
        std::cout << std::left << std::setw(8) << "ID" 
                  << std::setw(20) << "Diem den" 
                  << std::setw(15) << "Gia (VND)" 
                  << std::setw(10) << "Con trong" << "\n";
        printLine(63, '-');

        Node<Tour>* current = list.getHead();
        while (current != nullptr) {
            const Tour& t = current->data;
            std::cout << std::left << std::setw(8) << t.tourId
                      << std::setw(20) << t.destination
                      << std::setw(15) << std::fixed << std::setprecision(0) << t.price
                      << std::setw(10) << t.availableSeats << "\n";
            current = current->next;
        }
        printLine(63, '=');
    }

    // In danh sách Khách hàng
    static void printCustomerTable(const LinkedList<Customer>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Danh sach Khach hang hien tai dang trong.\n";
            return;
        }

        printLine(70, '=');
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(25) << "Ho va Ten" 
                  << std::setw(15) << "So dien thoai" 
                  << std::setw(20) << "Email" << "\n";
        printLine(70, '-');

        Node<Customer>* current = list.getHead();
        while (current != nullptr) {
            const Customer& c = current->data;
            std::cout << std::left << std::setw(10) << c.customerId
                      << std::setw(25) << c.fullName
                      << std::setw(15) << c.phoneNumber
                      << std::setw(20) << c.email << "\n";
            current = current->next;
        }
        printLine(70, '=');
    }

    // In danh sách Booking
    static void printBookingTable(const LinkedList<Booking>& list) {
        if (list.getSize() == 0) {
            std::cout << "-> Khong co du lieu Booking.\n";
            return;
        }

        printLine(80, '=');
        std::cout << std::left << std::setw(10) << "Book ID" 
                  << std::setw(10) << "Khach ID" 
                  << std::setw(10) << "Tour ID" 
                  << std::setw(10) << "So khach" 
                  << std::setw(15) << "Ngay dat" 
                  << std::setw(15) << "Trang thai" << "\n";
        printLine(80, '-');

        Node<Booking>* current = list.getHead();
        while (current != nullptr) {
            const Booking& b = current->data;
            std::cout << std::left << std::setw(10) << b.bookingId
                      << std::setw(10) << b.customer.customerId
                      << std::setw(10) << b.tour.tourId
                      << std::setw(10) << b.numberOfPeople
                      << std::setw(15) << b.bookingDate
                      << std::setw(15) << b.status << "\n";
            current = current->next;
        }
        printLine(80, '=');
    }

    // ==========================================
    // 3. Các hàm nhập dữ liệu (Input)
    // ==========================================

    // Nhập thông tin Tour
    static Tour inputTour() {
        Tour t;
        std::cout << "\n--- NHAP THONG TIN TOUR ---\n";
        std::cout << "Nhap ID Tour: ";
        std::cin >> t.tourId;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Xóa bộ đệm
        std::cout << "Nhap Ten Tour: ";
        std::getline(std::cin, t.tourName);
        
        std::cout << "Nhap Diem den: ";
        std::getline(std::cin, t.destination);
        
        std::cout << "Nhap Gia (VND): ";
        std::cin >> t.price;
        
        std::cout << "Nhap So ngay: ";
        std::cin >> t.durationDays;
        
        std::cout << "Nhap So cho con trong: ";
        std::cin >> t.availableSeats;
        
        std::cout << "Nhap Suc chua toi da: ";
        std::cin >> t.maxCapacity;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nhap Ngay khoi hanh (DD/MM/YYYY): ";
        std::getline(std::cin, t.departureDate);
        
        std::cout << "Nhap Trang thai (active/inactive): ";
        std::getline(std::cin, t.status);
        
        return t;
    }

    static Employee inputEmployee() {
        Employee e;
        std::cout << "\n--- NHAP THONG TIN NHAN VIEN ---\n";
        std::cout << "Nhap ID Nhan vien: ";
        std::cin >> e.employeeId;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nhap Ho va Ten: ";
        std::getline(std::cin, e.fullName);
        
        std::cout << "Nhap Chuc vu: ";
        std::getline(std::cin, e.position);
        
        return e;
    }

    // Nhập thông tin Khách hàng
    static Customer inputCustomer() {
        Customer c;
        std::cout << "\n--- NHAP THONG TIN KHACH HANG ---\n";
        std::cout << "Nhap ID Khach hang: ";
        std::cin >> c.customerId;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nhap Ho va Ten: ";
        std::getline(std::cin, c.fullName);
        
        std::cout << "Nhap So dien thoai: ";
        std::getline(std::cin, c.phoneNumber);
        
        std::cout << "Nhap Email: ";
        std::getline(std::cin, c.email);
        
        return c;
    }

    // Nhập thông tin Booking (Yêu cầu truyền vào đối tượng Customer và Tour đã có sẵn)
    static Booking inputBooking(const Customer& customer, const Tour& tour) {
        Booking b;
        // Gán tham chiếu đối tượng (hoặc copy tùy theo thiết kế struct/class của bạn)
        b.customer = customer;
        b.tour = tour;
        
        std::cout << "\n--- NHAP THONG TIN BOOKING ---\n";
        std::cout << "Nhap ID Booking: ";
        std::cin >> b.bookingId;
        
        std::cout << "Nhap So luong khach: ";
        std::cin >> b.numberOfPeople;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nhap Ngay dat (DD/MM/YYYY): ";
        std::getline(std::cin, b.bookingDate);
        
        b.status = "Pending"; // Mặc định trạng thái khi mới tạo
        
        return b;
    }
};

#endif // CONSOLE_UI_H