#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <string>
#include <limits>
#include <functional> // Thêm thư viện để truyền hàm validation như một tham số
#include "../models/Tour.h"
#include "../models/Customer.h"
#include "../models/Employee.h"
#include "../models/Booking.h"
#include "../utils/Validation.h"

using namespace std;

/**
 * @class InputHandler
 * @brief Handles all user interactions for data entry.
 * Tightly coupled with Validation to ensure clean data.
 */
class InputHandler
{
private:
    /**
     * @brief Hàm hỗ trợ nhập chuỗi an toàn kết hợp Validation
     */
    static string getValidString(const string& prompt, function<bool(const string&)> validator, const string& errorMsg = "Invalid input format.") 
    {
        string input;
        while (true) 
        {
            cout << prompt;
            getline(cin, input);
            
            if (Validation::isEmpty(input)) 
            {
                cout << "[!] Error: Input cannot be empty. Please try again.\n";
                continue;
            }
            if (validator != nullptr && !validator(input)) 
            {
                cout << "[!] Error: " << errorMsg << " Please try again.\n";
                continue;
            }
            return input;
        }
    }

    /**
     * @brief Hàm hỗ trợ nhập số (int, double,...) an toàn kết hợp Validation
     */
    template <typename T>
    static T getValidNumber(const string& prompt, function<bool(T)> validator, const string& errorMsg = "Invalid numeric value.") 
    {
        T input;
        while (true) 
        {
            cout << prompt;
            if (cin >> input) 
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (validator != nullptr && !validator(input)) 
                {
                    cout << "[!] Error: " << errorMsg << " Please try again.\n";
                    continue;
                }
                return input;
            }
            cout << "[!] Error: Invalid data type. Expected a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

public:
    static Tour inputTour()
    {
        Tour t;
        cout << "\n--- ENTER TOUR INFORMATION ---\n";
        t.tourId         = getValidString("Enter Tour ID: ", Validation::isValidId, "Wrong ID format.");
        
        t.tourName       = getValidString("Enter Tour Name: ", Validation::isValidName, "Invalid name format.");
        
        t.destination    = getValidString("Enter Destination: ", nullptr); 
        
        t.price          = getValidNumber<double>("Enter Price (VND): ", Validation::isValidPrice, "Price must be valid.");
        t.durationDays   = getValidNumber<int>("Enter Number of Days: ", Validation::isValidDuration, "Invalid duration.");
        t.availableSeats = getValidNumber<int>("Enter Available Seats: ", Validation::isValidSeats, "Invalid seats number.");
        t.maxCapacity    = getValidNumber<int>("Enter Maximum Capacity: ", Validation::isValidSeats, "Invalid maximum capacity.");
        t.departureDate  = getValidString("Enter Departure Date (DD/MM/YYYY): ", Validation::isValidDate, "Date must be DD/MM/YYYY.");
        t.status         = getValidString("Enter Status (active/inactive): ", Validation::isValidTourStatus, "Status must be active or inactive.");

        return t;
    }

    static Employee inputEmployee()
    {
        Employee e;
        cout << "\n--- ENTER EMPLOYEE INFORMATION ---\n";
        
        e.employeeId = getValidString("Enter Employee ID: ", Validation::isValidId, "Wrong ID format.");
        e.fullName   = getValidString("Enter Full Name: ", Validation::isValidName, "Invalid name format.");
        e.position   = getValidString("Enter Position: ", Validation::isValidPosition, "Invalid position format.");

        return e;
    }

    static Customer inputCustomer()
    {
        Customer c;
        cout << "\n--- ENTER CUSTOMER INFORMATION ---\n";
        
        c.customerId  = getValidString("Enter Customer ID: ", Validation::isValidId, "Wrong ID format.");
        c.fullName    = getValidString("Enter Full Name: ", Validation::isValidName, "Invalid name format.");
        c.phoneNumber = getValidString("Enter Phone Number: ", Validation::isValidPhoneNumber, "Invalid phone number.");
        c.email       = getValidString("Enter Email: ", Validation::isValidEmail, "Invalid email format.");

        return c;
    }

    static Booking inputBooking(const Customer &customer, const Tour &tour)
    {
        Booking b;
        b.customer = customer;
        b.tour = tour;

        cout << "\n--- ENTER BOOKING INFORMATION ---\n";
        
        b.bookingId      = getValidString("Enter Booking ID: ", Validation::isValidId, "Wrong ID format.");
        b.numberOfPeople = getValidNumber<int>("Enter Number of People: ", Validation::isValidNumberOfPeople, "Invalid number of people.");
        b.bookingDate    = getValidString("Enter Booking Date (DD/MM/YYYY): ", Validation::isValidDate, "Date must be DD/MM/YYYY.");
        b.status         = "Pending";

        return b;
    }
};

#endif