// ==========================================
// File: utils/ConsoleUI.h
// Description: UI for tables, data entry, and Console utilities
// ==========================================
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "../core/LinkedList.h"
#include "../models/Tour.h"
#include "../models/Customer.h"
#include "../models/Booking.h"
#include "../models/Employee.h"

using namespace std;

class ConsoleUI
{
public:
    static void inputSafeInt(int &value, const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break; 
        } else {
            std::cout << "-> Error: Please enter a valid integer. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

    static void InputSafeString(string &value, const string &prompt) {
    while (true) {
        cout << prompt;
        
        // Loại bỏ khoảng trắng/dấu xuống dòng còn sót lại từ các lệnh cin >> trước đó
        cin >> ws; 

        if (getline(cin, value)) {
            // Kiểm tra nếu chuỗi không chỉ toàn khoảng trắng
            if (!value.empty()) {
                break; 
            }
        }
        cout << "-> Error: Input cannot be empty. Try again: " << endl;
    }
}

static void inputSafeDouble(double &value, const string &prompt) {
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Nhập thành công số, dọn dẹp bộ đệm cho các lệnh sau
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } else {
            cout << "-> Error: Please enter a valid decimal number. Try again: " << endl;
            cin.clear(); // Xóa trạng thái lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
        }
    }
}

    // ==========================================
    // 1. Screen Utilities
    // ==========================================
    static void successMessage(const string &message)
    {
        cout << ">> " << message << "\n";
    }

        static void errorMessage(const string &message)
        {
            cout << "!! " << message << "\n";
        }
        
    static void clearScreen()
    {
        cout << "\033[2J\033[1;1H";
#if defined(_WIN32)
        system("cls");
#else
        system("clear");
#endif
    }
    static void clearBuffer()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    static void pauseScreen()
    {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static void printLine(int length = 85, char ch = '-')
    {
        cout << string(length, ch) << "\n";
    }

    // ==========================================
    // 2. Data Tables (Output)
    // ==========================================

    static void printEmployeeTable(const LinkedList<Employee> &list)
    {
        if (list.getSize() == 0)
        {
            cout << "-> Employee list is currently empty.\n";
            return;
        }

        printLine(60, '=');
        cout << left << setw(10) << "ID"
                  << setw(30) << "Full Name"
                  << setw(20) << "Position" << "\n";
        printLine(60, '-');

        Node<Employee> *current = list.getHead();
        while (current != nullptr)
        {
            const Employee &e = current->data;
            cout << left << setw(10) << e.employeeId
                      << setw(30) << e.fullName
                      << setw(20) << e.position << "\n";
            current = current->next;
        }
        printLine(60, '=');
    }

    static void printTourTable(const LinkedList<Tour> &list)
    {
        if (list.getSize() == 0)
        {
            cout << "-> Tour list is currently empty.\n";
            return;
        }

        printLine(75, '=');
        cout << left << setw(8) << "ID"
                  << setw(25) << "Destination"
                  << setw(15) << "Price ($)"
                  << setw(12) << "Available"
                  << setw(10) << "Status" << "\n";
        printLine(75, '-');

        Node<Tour> *current = list.getHead();
        while (current != nullptr)
        {
            const Tour &t = current->data;
            cout << left << setw(8) << t.tourId
                      << setw(25) << t.destination
                      << setw(15) << fixed << setprecision(2) << t.price
                      << setw(12) << t.availableSeats
                      << setw(10) << t.status << "\n";
            current = current->next;
        }
        printLine(75, '=');
    }

    static void printCustomerTable(const LinkedList<Customer> &list)
    {
        if (list.getSize() == 0)
        {
            cout << "-> Customer list is currently empty.\n";
            return;
        }

        printLine(85, '=');
        cout << left << setw(10) << "ID"
                  << setw(25) << "Full Name"
                  << setw(20) << "Phone Number"
                  << setw(25) << "Email" << "\n";
        printLine(85, '-');

        Node<Customer> *current = list.getHead();
        while (current != nullptr)
        {
            const Customer &c = current->data;
            cout << left << setw(10) << c.customerId
                      << setw(25) << c.fullName
                      << setw(20) << c.phoneNumber
                      << setw(25) << c.email << "\n";
            current = current->next;
        }
        printLine(85, '=');
    }

    static void printBookingTable(const LinkedList<Booking> &list)
    {
        if (list.getSize() == 0)
        {
            cout << "-> No booking records found.\n";
            return;
        }

        printLine(85, '=');
        cout << left << setw(10) << "BookID"
                  << setw(10) << "CustID"
                  << setw(10) << "TourID"
                  << setw(10) << "Guests"
                  << setw(15) << "Book Date"
                  << setw(15) << "Status" << "\n";
        printLine(85, '-');

        Node<Booking> *current = list.getHead();
        while (current != nullptr)
        {
            const Booking &b = current->data;
            cout << left << setw(10) << b.bookingId
                      << setw(10) << b.customer.customerId
                      << setw(10) << b.tour.tourId
                      << setw(10) << b.numberOfPeople
                      << setw(15) << b.bookingDate
                      << setw(15) << b.status << "\n";
            current = current->next;
        }
        printLine(85, '=');
    }
};
#endif // CONSOLE_UI_H