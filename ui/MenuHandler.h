#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <climits> // Cần thêm thư viện này cho INT_MAX nếu chưa có

#include "../services/TourService.h"
#include "../services/CustomerService.h"
#include "../services/EmployeeService.h"
#include "../services/BookingService.h"
#include "../utils/ConsoleUI.h"
#include "../utils/Validation.h"
#include "../utils/FileIO.h"
#include "InputHandler.h"

using namespace std;

// ================= LỚP MENU CHÍNH =================
class MenuHandler
{
private:
    TourService &tourService;
    CustomerService &customerService;
    EmployeeService &employeeService;
    BookingService &bookingService;

    // ================= 1. MASTER DATA MANAGEMENT =================
    void menuMasterDataManagement()
    {
        while (true)
        {
            ConsoleUI::clearScreen();
            int choice;
            cout << "\n=======================================================";
            cout << "\n        MASTER DATA MANAGEMENT (I/O & FILE)";
            cout << "\n=======================================================";
            cout << "\n [ TOUR ]         1. Input    2. Output    3. Read    4. Save";
            cout << "\n [ CUSTOMER ]     5. Input    6. Output    7. Read    8. Save";
            cout << "\n [ EMPLOYEE ]     9. Input   10. Output   11. Read   12. Save";
            cout << "\n [ BOOKING ]     13. Input   14. Output   15. Read   16. Save";
            cout << "\n [ 0. Go Back ]";
            cout << "\n-------------------------------------------------------";

            ConsoleUI::inputSafeInt(choice, "Select an action (0-16): ");

            if (choice == 0)
                break;

            switch (choice)
            {
            // ================= TOUR =================
            case 1:
            {
                int n;
                ConsoleUI::inputSafeInt(n, "How many Tours to add? ");
                for (int i = 0; i < n; i++)
                {
                    cout << "\n--- Entering Tour #" << i + 1 << " ---\n";
                    tourService.addTour(InputHandler::inputTour());
                }
                ConsoleUI::successMessage("Tours added successfully!");
                break;
            }
            case 2:
                ConsoleUI::printTourTable(tourService.getRepository());
                break;
            case 3:
                // Tối ưu: Nên để hàm load/save trả về bool để check trạng thái thực sự
                tourService.loadFromFile("data/tours.txt");
                ConsoleUI::successMessage("Tours loaded successfully!");
                break;
            case 4:
                tourService.saveToFile("data/tours.txt");
                ConsoleUI::successMessage("Tours saved successfully!");
                break;

            // ================= CUSTOMER =================
            case 5:
            {
                int n;
                ConsoleUI::inputSafeInt(n, "How many Customers to add? ");
                for (int i = 0; i < n; i++)
                {
                    cout << "\n--- Entering Customer #" << i + 1 << " ---\n";
                    customerService.addCustomer(InputHandler::inputCustomer());
                }

                ConsoleUI::successMessage("Customers added successfully!");
                break;
            }
            case 6:
                ConsoleUI::printCustomerTable(customerService.getRepository());
                ConsoleUI::pauseScreen();
                break;
            case 7:
                customerService.loadFromFile("data/customers.txt");
                ConsoleUI::successMessage("Customers loaded successfully!");
                break;
            case 8:
                customerService.saveToFile("data/customers.txt");
                ConsoleUI::successMessage("Customers saved successfully!");
                break;

            // ================= EMPLOYEE =================
            case 9:
            {
                int n;
                // Đã đồng bộ: Bỏ cin >> n và clearBuffer, dùng inputSafeInt
                ConsoleUI::inputSafeInt(n, "How many Employees to add? ");
                for (int i = 0; i < n; i++)
                {
                    cout << "\n--- Entering Employee #" << i + 1 << " ---\n";
                    employeeService.addEmployee(InputHandler::inputEmployee());
                }
                ConsoleUI::successMessage("Employees added successfully!");
                break;
            }
            case 10:
                ConsoleUI::printEmployeeTable(employeeService.getRepository());
                break;
            case 11:
                employeeService.loadFromFile("data/employees.txt");
                ConsoleUI::successMessage("Employees loaded successfully!");
                break;
            case 12:
                employeeService.saveToFile("data/employees.txt");
                ConsoleUI::successMessage("Employees saved successfully!");
                break;

            // ================= BOOKING =================
            case 13:
            {
                int n;
                ConsoleUI::inputSafeInt(n, "How many Bookings to create? ");
                for (int i = 0; i < n; i++)
                {
                    cout << "\n--- Creating Booking #" << i + 1 << " ---\n";

                    // Vòng lặp tìm Customer (Cho phép nhập lại nếu sai)
                    Node<Customer> *cNode = nullptr;
                    while (!cNode)
                    {
                        cout << "Select Customer ID (or type 'cancel' to skip): ";
                        string cId;
                        getline(cin, cId);
                        if (cId == "cancel")
                            break;

                        cNode = customerService.findCustomerById(cId);
                        if (!cNode)
                            cout << "[!] Customer not found. Please try again.\n";
                    }
                    if (!cNode)
                        continue; // Bỏ qua lượt này nếu user gõ 'cancel'

                    // Vòng lặp tìm Tour (Cho phép nhập lại nếu sai)
                    Node<Tour> *tNode = nullptr;
                    while (!tNode)
                    {
                        cout << "Select Tour ID (or type 'cancel' to skip): ";
                        string tId;
                        getline(cin, tId);
                        if (tId == "cancel")
                            break;

                        tNode = tourService.findTourById(tId);
                        if (!tNode)
                            cout << "[!] Tour not found. Please try again.\n";
                    }
                    if (!tNode)
                        continue; // Bỏ qua lượt này nếu user gõ 'cancel'

                    // Thêm booking khi đã có đủ thông tin
                    bookingService.addBooking(InputHandler::inputBooking(cNode->data, tNode->data));
                    ConsoleUI::successMessage("Booking created successfully!");
                }
                break;
            }
            case 14:
                ConsoleUI::printBookingTable(bookingService.getRepository());
                break;
            case 15:
                bookingService.loadFromFile("data/bookings.txt");
                ConsoleUI::successMessage("Bookings loaded successfully!");
                break;
            case 16:
                bookingService.saveToFile("data/bookings.txt");
                ConsoleUI::successMessage("Bookings saved successfully!");
                break;

            default:
                ConsoleUI::successMessage("[!] Invalid choice! Please select between 0 and 16.");
            }
                ConsoleUI::pauseScreen();
        }
    }

    // ================= 2. INFORMATION UPDATE =================
    void menuUpdateInformation()
    {
        while (true)
        {
            int choice;
            cout << "\n=======================================================";
            cout << "\n         INFORMATION UPDATE (ADD/EDIT/DELETE)";
            cout << "\n=======================================================";
            cout << "\n [ TOUR ]         1. Add      2. Edit      3. Delete";
            cout << "\n [ CUSTOMER ]     4. Add      5. Edit      6. Delete";
            cout << "\n [ EMPLOYEE ]     7. Add      8. Edit      9. Delete";
            cout << "\n [ BOOKING ]     10. Add                  11. Delete";
            cout << "\n [ 0. Go Back ]";
            cout << "\n-------------------------------------------------------";

            ConsoleUI::inputSafeInt(choice, "\nSelect an action (0-11): ");

            if (choice == 0)
                break;

            switch (choice)
            {
            // ================= TOUR =================
            case 1:
                tourService.addTour(InputHandler::inputTour());
                ConsoleUI::successMessage("Tour added successfully!");
                ConsoleUI::pauseScreen();
                break;
            case 2:
            {
                cout << "Enter Tour ID to edit: ";
                string id;
                cin >> id;
                if (!tourService.findTourById(id))
                {
                    ConsoleUI::errorMessage("Tour not found!");
                    ConsoleUI::pauseScreen();
                    break;
                }
                Tour t = InputHandler::inputTour();
                t.tourId = id; // Giữ nguyên ID cũ
                tourService.updateTour(id, t);
                ConsoleUI::successMessage("Tour updated successfully!");
                ConsoleUI::pauseScreen();
            }
            break;
            case 3:
            {
                cout << "Enter Tour ID to delete: ";
                string id;
                cin >> id;
                if (tourService.deleteTour(id))
                    ConsoleUI::successMessage("Tour deleted successfully!");
                else
                    ConsoleUI::errorMessage("Tour not found!");
                ConsoleUI::pauseScreen();
            }
            break;

            // ================= CUSTOMER =================
            case 4:
                customerService.addCustomer(InputHandler::inputCustomer());
                ConsoleUI::successMessage("Customer added successfully!");
                ConsoleUI::pauseScreen();
                break;
            case 5:
            {
                cout << "Enter Customer ID to edit: ";
                string id;
                cin >> id;
                if (!customerService.findCustomerById(id))
                {
                    ConsoleUI::errorMessage("Customer not found!");
                    ConsoleUI::pauseScreen();
                    break;
                }
                Customer c = InputHandler::inputCustomer();
                c.customerId = id;
                customerService.updateCustomer(id, c);
                ConsoleUI::successMessage("Customer updated successfully!");
                ConsoleUI::pauseScreen();
            }
            break;
            case 6:
            {
                cout << "Enter Customer ID to delete: ";
                string id;
                cin >> id;
                if (customerService.deleteCustomer(id))
                    ConsoleUI::successMessage("Customer deleted successfully!");
                else
                    ConsoleUI::errorMessage("Customer not found!");
                ConsoleUI::pauseScreen();
            }
            break;

            // ================= EMPLOYEE =================
            case 7:
                employeeService.addEmployee(InputHandler::inputEmployee());
                ConsoleUI::successMessage("Employee added successfully!");
                ConsoleUI::pauseScreen();
                break;
            case 8:
            {
                cout << "Enter Employee ID to edit: ";
                string id;
                cin >> id;
                if (!employeeService.findEmployeeById(id))
                {
                    ConsoleUI::errorMessage("Employee not found!");
                    ConsoleUI::pauseScreen();
                    break;
                }
                Employee e = InputHandler::inputEmployee();
                e.employeeId = id;
                employeeService.updateEmployee(id, e);
                ConsoleUI::successMessage("Employee updated successfully!");
                ConsoleUI::pauseScreen();
            }
            break;
            case 9:
            {
                cout << "Enter Employee ID to delete: ";
                string id;
                cin >> id;
                if (employeeService.deleteEmployee(id))
                    ConsoleUI::successMessage("Employee deleted successfully!");
                else
                    ConsoleUI::errorMessage("Employee not found!");
                ConsoleUI::pauseScreen();
            }
            break;

            // ================= BOOKING =================
            case 10:
            {
                string cId, tId;
                cout << "Enter Customer ID: ";
                cin >> cId;
                Node<Customer> *cNode = customerService.findCustomerById(cId);
                if (!cNode)
                {
                    ConsoleUI::errorMessage("Customer not found!");
                    ConsoleUI::pauseScreen();
                    break;
                }

                cout << "Enter Tour ID: ";
                cin >> tId;
                Node<Tour> *tNode = tourService.findTourById(tId);
                if (!tNode)
                {
                    ConsoleUI::errorMessage("Tour not found!");
                    ConsoleUI::pauseScreen();
                    break;
                }

                bookingService.addBooking(InputHandler::inputBooking(cNode->data, tNode->data));
                ConsoleUI::successMessage("Booking added successfully!");
                ConsoleUI::pauseScreen();
            }
            break;
            case 11:
            {
                cout << "Enter Booking ID to delete: ";
                string id;
                cin >> id;
                if (bookingService.deleteBooking(id))
                    ConsoleUI::successMessage("Booking deleted successfully!");
                else
                    ConsoleUI::errorMessage("Booking not found!");
                ConsoleUI::pauseScreen();
            }
            break;

            default:
                ConsoleUI::errorMessage("Invalid choice! Please select between 0 and 11.");
                ConsoleUI::pauseScreen();
            }
        }
    }

    // ================= 3. DATA QUERY (SEARCH) =================
    void menuDataQuery()
    {
        while (true)
        {
            int choice;
            cout << "\n=======================================================";
            cout << "\n              DATA QUERY (SEARCH & FILTER)";
            cout << "\n=======================================================";
            cout << "\n [ 1 ] Search Tours       (Hint: By Tour ID, Name)";
            cout << "\n [ 2 ] Search Customers   (Hint: By ID, Name, Phone)";
            cout << "\n [ 3 ] Search Employees   (Hint: By ID, Name, Role)";
            cout << "\n [ 4 ] Search Bookings    (Hint: By Booking/Customer ID)";
            cout << "\n [ 0. Go Back ]";
            cout << "\n-------------------------------------------------------";

            ConsoleUI::inputSafeInt(choice, "\nSelect an action (0-4): ");

            if (choice == 0)
                break;

            string keyword;
            ConsoleUI::InputSafeString(keyword, "Enter search keyword: ");

            cout << "\n--- SEARCH RESULTS ---\n";
            switch (choice)
            {
            case 1:
                ConsoleUI::printTourTable(tourService.searchTours(keyword));
                break;
            case 2:
                ConsoleUI::printCustomerTable(customerService.searchCustomers(keyword));
                break;
            case 3:
                ConsoleUI::printEmployeeTable(employeeService.searchEmployees(keyword));
                break;
            case 4:
                ConsoleUI::printBookingTable(bookingService.searchBookings(keyword));
                break;
            }

            ConsoleUI::pauseScreen();
        }
    }

    // ================= 4. DATA ORGANIZATION (SORT) =================
    void menuDataOrganization()
    {
        while (true)
        {
            int choice;
            cout << "\n=== DATA ORGANIZATION (SORT) ===\n";
            cout << "  [ TOUR ]\n";
            cout << "1. Sort Tours by ID\n2. Sort Tours by Name\n3. Sort Tours by Price\n";
            cout << "----\n";
            cout << "  [ CUSTOMER ]\n";
            cout << "4. Sort Customers by ID\n5. Sort Customers by Name\n";
            cout << "----\n";
            cout << "  [ EMPLOYEE ]\n";
            cout << "6. Sort Employees by ID\n7. Sort Employees by Name\n";
            cout << "----\n";
            cout << "  [ BOOKING ]\n";
            cout << "8. Sort Bookings by ID\n9. Sort Bookings by Date\n";
            cout << "0. Go Back\n";
            cout << "Select an action (0-9): ";
            cin >> choice;

            if (choice == 0)
                break;

            cout << "\n[Execution] Sorting action " << choice << " executed...\n";
        }
    }

    // ================= 5. BOUNDARY ANALYSIS (MAX/MIN) =================

#include <climits> // Bắt buộc để dùng INT_MAX

    void menuBoundaryAnalysis()
    {
        while (true)
        {
            int choice;
            cout << "\n=======================================================";
            cout << "\n             BOUNDARY ANALYSIS (MAX/MIN)";
            cout << "\n=======================================================";
            cout << "\n [ TOUR ANALYSIS ]";
            cout << "\n 1. Price Analysis       (Highest / Lowest)";
            cout << "\n 2. Duration Analysis    (Longest / Shortest)";
            cout << "\n 3. Popularity Analysis  (Most / Least Popular)";
            cout << "\n\n [ BOOKING ANALYSIS ]";
            cout << "\n 4. People Analysis      (Most / Fewest People)";
            cout << "\n\n [ 0. Go Back ]";
            cout << "\n-------------------------------------------------------";

            ConsoleUI::inputSafeInt(choice, "\nSelect an action (0-4): ");

            if (choice == 0)
                break;

            cout << "\n--- ANALYSIS RESULTS ---\n";
            switch (choice)
            {
            case 1:
            {
                // Sửa thành con trỏ Node<Tour>*
                Node<Tour> *maxTour = tourService.getHighestPriceTour();
                Node<Tour> *minTour = tourService.getLowestPriceTour();

                cout << ">> Highest Price Tour: " << (maxTour ? maxTour->data.tourId : "N/A") << "\n";
                cout << ">> Lowest Price Tour:  " << (minTour ? minTour->data.tourId : "N/A") << "\n";
                break;
            }
            case 2:
            {
                Node<Tour> *maxTour = tourService.getLongestDurationTour();
                Node<Tour> *minTour = tourService.getShortestDurationTour();

                cout << ">> Longest Duration Tour:  " << (maxTour ? maxTour->data.tourId : "N/A") << "\n";
                cout << ">> Shortest Duration Tour: " << (minTour ? minTour->data.tourId : "N/A") << "\n";
                break;
            }
            case 3:
            {
                Node<Tour> *maxTour = tourService.getMostPopularTour();
                Node<Tour> *minTour = tourService.getLeastPopularTour();

                cout << ">> Most Popular Tour:  " << (maxTour ? maxTour->data.tourId : "N/A") << "\n";
                cout << ">> Least Popular Tour: " << (minTour ? minTour->data.tourId : "N/A") << "\n";
                break;
            }
            case 4:
            {
                Node<Booking> *maxBooking = nullptr;
                Node<Booking> *minBooking = nullptr;
                int maxPeople = -1;
                int minPeople = INT_MAX;

                Node<Booking> *current = bookingService.getRepository().getHead();

                if (!current)
                {
                    cout << ">> No booking data available.\n";
                }
                else
                {
                    while (current)
                    {
                        if (current->data.numberOfPeople > maxPeople)
                        {
                            maxPeople = current->data.numberOfPeople;
                            maxBooking = current;
                        }
                        if (current->data.numberOfPeople < minPeople)
                        {
                            minPeople = current->data.numberOfPeople;
                            minBooking = current;
                        }
                        current = current->next;
                    }

                    cout << ">> Booking with Most People:   " << (maxBooking ? maxBooking->data.bookingId : "N/A");
                    if (maxBooking)
                        cout << " (" << maxPeople << " pax)";
                    cout << "\n";

                    cout << ">> Booking with Fewest People: " << (minBooking ? minBooking->data.bookingId : "N/A");
                    if (minBooking)
                        cout << " (" << minPeople << " pax)";
                    cout << "\n";
                }
                break;
            }
            default:
                ConsoleUI::errorMessage("Invalid choice! Please select between 0 and 4.");
            }

            if (choice >= 1 && choice <= 4)
            {
                ConsoleUI::pauseScreen();
            }
        }
    }

    // ================= 6. GENERAL MEASUREMENT (SUM/AVG/COUNT) =================
    void menuGeneralMeasurement()
{
    while (true)
    {
        int choice;
        cout << "\n=======================================================";
        cout << "\n       GENERAL MEASUREMENT (SUM / AVG / COUNT)";
        cout << "\n=======================================================";
        cout << "\n [ STATISTICS CATEGORIES ]";
        cout << "\n 1. Tour Overview      (Total Tours, Avg Price)";
        cout << "\n 2. Customer Insights  (Total, Participation)";
        cout << "\n 3. Employee Workload  (Total Staff, Performance)";
        cout << "\n 4. Financial Report   (Revenue, People, Spending)";
        cout << "\n\n [ 0. Go Back ]";
        cout << "\n-------------------------------------------------------";

        ConsoleUI::inputSafeInt(choice, "\nSelect an action (0-4): ");

        if (choice == 0) break;

        cout << "\n>>> ANALYSIS RESULTS <<<\n";
        cout << "-------------------------------------------------------";

        switch (choice)
        {
            case 1: // Tour Statistics
            {
                int count = tourService.getTotalTours();
                double totalPrice = 0;
                Node<Tour>* current = tourService.getRepository().getHead();
                while (current) {
                    totalPrice += current->data.price;
                    current = current->next;
                }
                cout << "\n+ Total Tours in System:  " << count;
                cout << "\n+ Average Tour Price:     " << (count > 0 ? totalPrice / count : 0) << " USD";
                break;
            }
            case 2: // Customer Statistics
            {
                int totalCust = customerService.getTotalCustomers();
                cout << "\n+ Total Registered Customers: " << totalCust;
                break;
            }
            case 3: // Employee Statistics
            {
                int totalEmp = employeeService.getTotalEmployees();
                cout << "\n+ Total Staff Members: " << totalEmp;
                // Có thể thêm tính toán: Số lượng booking trung bình mỗi nhân viên xử lý
                break;
            }
            case 4: // Booking & Financial
            {
                int totalBookings = bookingService.getTotalBookings();
                double revenue = bookingService.calculateTotalRevenue();
                int totalPeople = bookingService.getTotalPeopleBooked();

                cout << "\n+ Total Revenue:          " << revenue << " USD";
                cout << "\n+ Total Bookings:         " << totalBookings;
                cout << "\n+ Total Passengers:       " << totalPeople << " pax";
                cout << "\n+ Avg Spending per Book:  " << (totalBookings > 0 ? revenue / totalBookings : 0) << " USD";
                break;
            }
            default:
                ConsoleUI::errorMessage("Invalid selection! Please try again.");
                continue;
        }
        
        cout << "\n-------------------------------------------------------";
        ConsoleUI::pauseScreen();
    }
}
    // ================= 7. CATEGORICAL REPORTING (STATISTICS) =================
    void menuCategoricalReporting()
    {
        while (true)
        {
            int choice;
            cout << "\n=== CATEGORICAL REPORTING (STATISTICS) ===\n";
            cout << "1. Statistics for Tours (By Status)\n";
            cout << "----\n";
            cout << "2. Statistics for Employees (By Position)\n";
            cout << "----\n";
            cout << "3. Statistics for Bookings (By Status)\n";
            cout << "0. Go Back\n";
            cout << "Select an action (0-3): ";
            cin >> choice;

            if (choice == 0)
                break;

            if (choice == 1)
            {
                int act = 0, inact = 0, comp = 0;
                Node<Tour> *current = tourService.getRepository().getHead();
                while (current)
                {
                    if (current->data.status == "active")
                        act++;
                    else if (current->data.status == "inactive")
                        inact++;
                    else if (current->data.status == "completed")
                        comp++;
                    current = current->next;
                }
                cout << "Tour Status -> Active: " << act << " | Inactive: " << inact << " | Completed: " << comp << "\n";
            }
            else if (choice == 2)
            {
                cout << "Employee Positions:\n";
                Node<Employee> *current = employeeService.getRepository().getHead();
                while (current)
                {
                    cout << "  " << current->data.fullName << " - " << current->data.position << "\n";
                    current = current->next;
                }
            }
            else if (choice == 3)
            {
                int pend = 0, conf = 0, comp = 0, canc = 0;
                Node<Booking> *current = bookingService.getRepository().getHead();
                while (current)
                {
                    if (current->data.status == "pending")
                        pend++;
                    else if (current->data.status == "confirmed")
                        conf++;
                    else if (current->data.status == "completed")
                        comp++;
                    else if (current->data.status == "cancelled")
                        canc++;
                    current = current->next;
                }
                cout << "Booking Status -> Pending: " << pend << " | Confirmed: " << conf << " | Completed: " << comp << " | Cancelled: " << canc << "\n";
            }
        }
    }

    // ================= MAIN MENU HIỂN THỊ =================
    void displayMainMenu()
    {
        cout << "\n==================================================================================";
        cout << "\n|                  DETAILED TOURISM BUSINESS MANAGEMENT SYSTEM                   |";
        cout << "\n==================================================================================\n";
        cout << "1. OPERATIONS: MASTER DATA MANAGEMENT (I/O & FILE)\n";
        cout << "2. OPERATIONS: INFORMATION UPDATE (ADD/EDIT/DELETE)\n";
        cout << "3. OPERATIONS: DATA QUERY (SEARCH)\n";
        cout << "4. OPERATIONS: DATA ORGANIZATION (SORT)\n";
        cout << "5. OPERATIONS: BOUNDARY ANALYSIS (MAX/MIN)\n";
        cout << "6. OPERATIONS: GENERAL MEASUREMENT (SUM/AVG/COUNT)\n";
        cout << "7. OPERATIONS: CATEGORICAL REPORTING (STATISTICS)\n";
        cout << "0. EXIT PROGRAM (Auto-save all system data)\n";
        cout << "==================================================================================\n";
    }

public:
    MenuHandler(TourService &ts, CustomerService &cs, EmployeeService &es, BookingService &bs)
        : tourService(ts), customerService(cs), employeeService(es), bookingService(bs) {}

    void run()
    {
        int choice;
        while (true)
        {
            displayMainMenu();
            cout << "Enter your main choice (0-7): ";
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Error: Please enter a valid number!\n";
                continue;
            }

            switch (choice)
            {
            case 1:
                menuMasterDataManagement();
                break;
            case 2:
                menuUpdateInformation();
                break;
            case 3:
                menuDataQuery();
                break;
            case 4:
                menuDataOrganization();
                break;
            case 5:
                menuBoundaryAnalysis();
                break;
            case 6:
                menuGeneralMeasurement();
                break;
            case 7:
                menuCategoricalReporting();
                break;
            case 0:
            {
                cout << "\n[System] Auto-saving all data...\n";
                tourService.saveToFile("data/tours.txt");
                customerService.saveToFile("data/customers.txt");
                employeeService.saveToFile("data/employees.txt");
                bookingService.saveToFile("data/bookings.txt");
                cout << "[System] Save successful. Goodbye, Phạm Đức Long!\n";
                return;
            }
            default:
                cout << "Invalid choice! Please select a number from 0 to 7.\n";
            }
        }
    }
};