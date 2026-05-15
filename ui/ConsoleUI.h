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

class ConsoleUI
{
public:
    // Helper for numeric validation to prevent "input lag/crash" if user enters text
    static void inputSafeInt(int &value, const std::string &prompt)
    {
        std::cout << prompt;
        while (!(std::cin >> value))
        {
            std::cout << "-> Error: Please enter a valid integer. Try again: ";
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard buffer
        }
    }

    static void InputSafeString(std::string &value, const std::string &prompt)
    {
        std::cout << prompt;
        std::getline(std::cin, value);
        while (value.empty())
        {
            std::cout << "-> Error: Input cannot be empty. Try again: ";
            std::getline(std::cin, value);
        }
    }
    static void inputSafeDouble(double &value, const std::string &prompt)
    {
        std::cout << prompt;
        while (!(std::cin >> value))
        {
            std::cout << "-> Error: Please enter a valid decimal number. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // ==========================================
    // 1. Screen Utilities
    // ==========================================
    static void successMessage(const std::string &message)
    {
        std::cout << ">> " << message << "\n";
    }

        static void errorMessage(const std::string &message)
        {
            std::cout << "!! " << message << "\n";
        }
        
    static void clearScreen()
    {
        std::cout << "\033[2J\033[1;1H";
#if defined(_WIN32)
        system("cls");
#else
        system("clear");
#endif
    }
    static void clearBuffer()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    static void pauseScreen()
    {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    static void printLine(int length = 85, char ch = '-')
    {
        std::cout << std::string(length, ch) << "\n";
    }

    // ==========================================
    // 2. Data Tables (Output)
    // ==========================================

    static void printEmployeeTable(const LinkedList<Employee> &list)
    {
        if (list.getSize() == 0)
        {
            std::cout << "-> Employee list is currently empty.\n";
            return;
        }

        printLine(60, '=');
        std::cout << std::left << std::setw(10) << "ID"
                  << std::setw(30) << "Full Name"
                  << std::setw(20) << "Position" << "\n";
        printLine(60, '-');

        Node<Employee> *current = list.getHead();
        while (current != nullptr)
        {
            const Employee &e = current->data;
            std::cout << std::left << std::setw(10) << e.employeeId
                      << std::setw(30) << e.fullName
                      << std::setw(20) << e.position << "\n";
            current = current->next;
        }
        printLine(60, '=');
    }

    static void printTourTable(const LinkedList<Tour> &list)
    {
        if (list.getSize() == 0)
        {
            std::cout << "-> Tour list is currently empty.\n";
            return;
        }

        printLine(75, '=');
        std::cout << std::left << std::setw(8) << "ID"
                  << std::setw(25) << "Destination"
                  << std::setw(15) << "Price ($)"
                  << std::setw(12) << "Available"
                  << std::setw(10) << "Status" << "\n";
        printLine(75, '-');

        Node<Tour> *current = list.getHead();
        while (current != nullptr)
        {
            const Tour &t = current->data;
            std::cout << std::left << std::setw(8) << t.tourId
                      << std::setw(25) << t.destination
                      << std::setw(15) << std::fixed << std::setprecision(2) << t.price
                      << std::setw(12) << t.availableSeats
                      << std::setw(10) << t.status << "\n";
            current = current->next;
        }
        printLine(75, '=');
    }

    static void printCustomerTable(const LinkedList<Customer> &list)
    {
        if (list.getSize() == 0)
        {
            std::cout << "-> Customer list is currently empty.\n";
            return;
        }

        printLine(85, '=');
        std::cout << std::left << std::setw(10) << "ID"
                  << std::setw(25) << "Full Name"
                  << std::setw(20) << "Phone Number"
                  << std::setw(25) << "Email" << "\n";
        printLine(85, '-');

        Node<Customer> *current = list.getHead();
        while (current != nullptr)
        {
            const Customer &c = current->data;
            std::cout << std::left << std::setw(10) << c.customerId
                      << std::setw(25) << c.fullName
                      << std::setw(20) << c.phoneNumber
                      << std::setw(25) << c.email << "\n";
            current = current->next;
        }
        printLine(85, '=');
    }

    static void printBookingTable(const LinkedList<Booking> &list)
    {
        if (list.getSize() == 0)
        {
            std::cout << "-> No booking records found.\n";
            return;
        }

        printLine(85, '=');
        std::cout << std::left << std::setw(10) << "BookID"
                  << std::setw(10) << "CustID"
                  << std::setw(10) << "TourID"
                  << std::setw(10) << "Guests"
                  << std::setw(15) << "Book Date"
                  << std::setw(15) << "Status" << "\n";
        printLine(85, '-');

        Node<Booking> *current = list.getHead();
        while (current != nullptr)
        {
            const Booking &b = current->data;
            std::cout << std::left << std::setw(10) << b.bookingId
                      << std::setw(10) << b.customer.customerId
                      << std::setw(10) << b.tour.tourId
                      << std::setw(10) << b.numberOfPeople
                      << std::setw(15) << b.bookingDate
                      << std::setw(15) << b.status << "\n";
            current = current->next;
        }
        printLine(85, '=');
    }
};
#endif // CONSOLE_UI_H