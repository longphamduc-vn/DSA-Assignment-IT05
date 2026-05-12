#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "../services/TourService.h"
#include "../services/CustomerService.h"
#include "../services/EmployeeService.h"
#include "../services/BookingService.h"
#include "../utils/ConsoleUI.h"
#include "../utils/Validation.h"
#include "../utils/FileIO.h"

using namespace std;

// ================= LỚP MENU CHÍNH =================
class Menu
{
private:
    TourService &tourService;
    CustomerService &customerService;
    EmployeeService &employeeService;
    BookingService &bookingService;

    // --- Helper Menu: Chọn Đối Tượng ---
    int selectEntity(const string &operationName)
    {
        int choice;
        cout << "\n=== OPERATIONS: " << operationName << " ===\n";
        cout << "1. Tour Object\n";
        cout << "2. Customer Object\n";
        cout << "3. Employee Object\n";
        cout << "4. Booking Object\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select an object (0-4): ";
        cin >> choice;
        return choice;
    }

    // ================= 1. MASTER DATA MANAGEMENT =================
    void menuMasterDataManagement()
    {
        while (true)
        {
            int choice = selectEntity("MASTER DATA MANAGEMENT (I/O & FILE)");
            if (choice == 0) break;

            int subChoice;
            cout << "\n--- MASTER DATA ACTIONS ---\n";
            cout << "1. Input data from keyboard\n";
            cout << "2. Output data table\n";
            cout << "3. Read data from file\n";
            cout << "4. Save data to file\n";
            cout << "0. Go Back\n";
            cout << "Select an action (0-4): ";
            cin >> subChoice;

            string entity = getEntityName(choice);

            switch (subChoice)
            {
            case 1:
            {
                cout << "\nHow many " << entity << " records do you want to input? ";
                int count;
                cin >> count;
                cin.ignore(10000, '\n');
                
                for (int i = 0; i < count; i++)
                {
                    cout << "\n--- Record " << (i+1) << " of " << count << " ---\n";
                    switch (choice)
                    {
                    case 1:
                    {
                        Tour tour = ConsoleUI::inputTour();
                        tourService.addTour(tour);
                        cout << "Tour added successfully!\n";
                    }
                    break;
                    case 2:
                    {
                        Customer customer = ConsoleUI::inputCustomer();
                        customerService.addCustomer(customer);
                        cout << "Customer added successfully!\n";
                    }
                    break;
                    case 3:
                    {
                        Employee employee = ConsoleUI::inputEmployee();
                        employeeService.addEmployee(employee);
                        cout << "Employee added successfully!\n";
                    }
                    break;
                    case 4:
                    {
                        cout << "Select Customer for Booking:\n";
                        ConsoleUI::printCustomerTable(customerService.getRepository());
                        string customerId;
                        cout << "Enter Customer ID: ";
                        getline(cin, customerId);
                        Node<Customer> *customerNode = customerService.findCustomerById(customerId);
                        if (customerNode == nullptr)
                        {
                            cout << "Customer not found!\n";
                            i--;
                            break;
                        }

                        cout << "Select Tour for Booking:\n";
                        ConsoleUI::printTourTable(tourService.getRepository());
                        string tourId;
                        cout << "Enter Tour ID: ";
                        getline(cin, tourId);
                        Node<Tour> *tourNode = tourService.findTourById(tourId);
                        if (tourNode == nullptr)
                        {
                            cout << "Tour not found!\n";
                            i--;
                            break;
                        }

                        Booking booking = ConsoleUI::inputBooking(customerNode->data, tourNode->data);
                        bookingService.addBooking(booking);
                        cout << "Booking added successfully!\n";
                    }
                    break;
                    }
                }
                break;
            }

            case 2:
            {
                switch (choice)
                {
                case 1:
                    ConsoleUI::printTourTable(tourService.getRepository());
                    break;
                case 2:
                    ConsoleUI::printCustomerTable(customerService.getRepository());
                    break;
                case 3:
                    ConsoleUI::printEmployeeTable(employeeService.getRepository());
                    break;
                case 4:
                    ConsoleUI::printBookingTable(bookingService.getRepository());
                    break;
                }
                break;
            }

            case 3:
            {
                cout << "Reading " << entity << " data from file...\n";
                switch (choice)
                {
                case 1:
                    tourService.loadFromFile("data/tours.txt");
                    cout << "Tours loaded successfully!\n";
                    break;
                case 2:
                    customerService.loadFromFile("data/customers.txt");
                    cout << "Customers loaded successfully!\n";
                    break;
                case 3:
                    employeeService.loadFromFile("data/employees.txt");
                    cout << "Employees loaded successfully!\n";
                    break;
                case 4:
                    bookingService.loadFromFile("data/bookings.txt");
                    cout << "Bookings loaded successfully!\n";
                    break;
                }
                break;
            }

            case 4:
            {
                cout << "Saving " << entity << " data to file...\n";
                switch (choice)
                {
                case 1:
                    tourService.saveToFile("data/tours.txt");
                    cout << "Tours saved successfully!\n";
                    break;
                case 2:
                    customerService.saveToFile("data/customers.txt");
                    cout << "Customers saved successfully!\n";
                    break;
                case 3:
                    employeeService.saveToFile("data/employees.txt");
                    cout << "Employees saved successfully!\n";
                    break;
                case 4:
                    bookingService.saveToFile("data/bookings.txt");
                    cout << "Bookings saved successfully!\n";
                    break;
                }
                break;
            }
            }

            if (subChoice == 0) continue;
            if (entity != "Unknown")
                cout << "\n[Execution] Executing action " << subChoice << " for " << entity << " Master Data...\n";
            else
                cout << "Invalid choice!\n";
        }
    }

    // ================= 2. INFORMATION UPDATE =================
    void menuUpdateInformation()
    {
        while (true)
        {
            int choice = selectEntity("INFORMATION UPDATE (ADD/EDIT/DELETE)");
            if (choice == 0) break;

            int subChoice;
            cout << "\n--- UPDATE ACTIONS ---\n";
            cout << "1. Add new record\n";
            cout << "2. Edit record by ID\n";
            cout << "3. Delete record by ID\n";
            cout << "0. Go Back\n";
            cout << "Select an action (0-3): ";
            cin >> subChoice;

            if (subChoice == 0) continue;

            switch (subChoice)
            {
            case 1:
            {
                switch (choice)
                {
                case 1:
                {
                    Tour tour = ConsoleUI::inputTour();
                    tourService.addTour(tour);
                    cout << "Tour added successfully!\n";
                }
                break;
                case 2:
                {
                    Customer customer = ConsoleUI::inputCustomer();
                    customerService.addCustomer(customer);
                    cout << "Customer added successfully!\n";
                }
                break;
                case 3:
                {
                    Employee employee = ConsoleUI::inputEmployee();
                    employeeService.addEmployee(employee);
                    cout << "Employee added successfully!\n";
                }
                break;
                case 4:
                {
                    cout << "Select Customer for Booking:\n";
                    ConsoleUI::printCustomerTable(customerService.getRepository());
                    string customerId;
                    cout << "Enter Customer ID: ";
                    cin >> customerId;
                    Node<Customer> *customerNode = customerService.findCustomerById(customerId);
                    if (customerNode == nullptr) { cout << "Customer not found!\n"; break; }

                    cout << "Select Tour for Booking:\n";
                    ConsoleUI::printTourTable(tourService.getRepository());
                    string tourId;
                    cout << "Enter Tour ID: ";
                    cin >> tourId;
                    Node<Tour> *tourNode = tourService.findTourById(tourId);
                    if (tourNode == nullptr) { cout << "Tour not found!\n"; break; }

                    Booking booking = ConsoleUI::inputBooking(customerNode->data, tourNode->data);
                    bookingService.addBooking(booking);
                    cout << "Booking added successfully!\n";
                }
                break;
                }
                break;
            }

            case 2:
            {
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter Tour ID to edit: ";
                    string tourId;
                    cin >> tourId;
                    Node<Tour> *tourNode = tourService.findTourById(tourId);
                    if (tourNode == nullptr) { cout << "Tour not found!\n"; break; }
                    
                    Tour updatedTour = ConsoleUI::inputTour();
                    updatedTour.tourId = tourId;
                    tourService.updateTour(tourId, updatedTour);
                    cout << "Tour updated successfully!\n";
                }
                break;
                case 2:
                {
                    cout << "Enter Customer ID to edit: ";
                    string customerId;
                    cin >> customerId;
                    Node<Customer> *customerNode = customerService.findCustomerById(customerId);
                    if (customerNode == nullptr) { cout << "Customer not found!\n"; break; }
                    
                    Customer updatedCustomer = ConsoleUI::inputCustomer();
                    updatedCustomer.customerId = customerId;
                    customerService.updateCustomer(customerId, updatedCustomer);
                    cout << "Customer updated successfully!\n";
                }
                break;
                case 3:
                {
                    cout << "Enter Employee ID to edit: ";
                    string employeeId;
                    cin >> employeeId;
                    Node<Employee> *employeeNode = employeeService.findEmployeeById(employeeId);
                    if (employeeNode == nullptr) { cout << "Employee not found!\n"; break; }
                    
                    Employee updatedEmployee = ConsoleUI::inputEmployee();
                    updatedEmployee.employeeId = employeeId;
                    employeeService.updateEmployee(employeeId, updatedEmployee);
                    cout << "Employee updated successfully!\n";
                }
                break;
                }
                break;
            }

            case 3:
            {
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter Tour ID to delete: ";
                    string tourId;
                    cin >> tourId;
                    if (!tourService.deleteTour(tourId)) { cout << "Tour not found!\n"; break; }
                    cout << "Tour deleted successfully!\n";
                }
                break;
                case 2:
                {
                    cout << "Enter Customer ID to delete: ";
                    string customerId;
                    cin >> customerId;
                    if (!customerService.deleteCustomer(customerId)) { cout << "Customer not found!\n"; break; }
                    cout << "Customer deleted successfully!\n";
                }
                break;
                case 3:
                {
                    cout << "Enter Employee ID to delete: ";
                    string employeeId;
                    cin >> employeeId;
                    if (!employeeService.deleteEmployee(employeeId)) { cout << "Employee not found!\n"; break; }
                    cout << "Employee deleted successfully!\n";
                }
                break;
                case 4:
                {
                    cout << "Enter Booking ID to delete: ";
                    string bookingId;
                    cin >> bookingId;
                    if (!bookingService.deleteBooking(bookingId)) { cout << "Booking not found!\n"; break; }
                    cout << "Booking deleted successfully!\n";
                }
                break;
                }
                break;
            }
            }

            string entity = getEntityName(choice);
            if (entity != "Unknown")
                cout << "\n[Execution] Executing action " << subChoice << " for " << entity << " Update...\n";
            else
                cout << "Invalid choice!\n";
        }
    }

    // ================= 3. DATA QUERY (SEARCH) =================
    void menuDataQuery()
    {
        while (true)
        {
            int choice = selectEntity("DATA QUERY (SEARCH)");
            if (choice == 0) break;

            string entity = getEntityName(choice);
            if (entity == "Unknown") { cout << "Invalid choice!\n"; continue; }

            string keyword;
            cout << "\n--- SEARCH " << entity << " ---\n";
            cout << "Enter ID or Name to search: ";
            cin.ignore(10000, '\n');
            getline(cin, keyword);

            LinkedList<Tour> tourResults;
            LinkedList<Customer> customerResults;
            LinkedList<Employee> employeeResults;
            LinkedList<Booking> bookingResults;

            if (choice == 1)
            {
                LinkedList<Tour> tourResults = tourService.searchTours(keyword);
                ConsoleUI::printTourTable(tourResults);
            }
            else if (choice == 2)
            {
                LinkedList<Customer> customerResults = customerService.searchCustomers(keyword);
                ConsoleUI::printCustomerTable(customerResults);
            }
            else if (choice == 3)
            {
                LinkedList<Employee> employeeResults = employeeService.searchEmployees(keyword);
                ConsoleUI::printEmployeeTable(employeeResults);
            }
            else if (choice == 4)
            {
                LinkedList<Booking> bookingResults = bookingService.searchBookings(keyword);
                ConsoleUI::printBookingTable(bookingResults);
            }

            cout << "\n[Execution] Search completed for '" << keyword << "' in " << entity << " data...\n";
        }
    }

    // ================= 4. DATA ORGANIZATION (SORT) =================
    void menuDataOrganization()
    {
        while (true)
        {
            int choice = selectEntity("DATA ORGANIZATION (SORT)");
            if (choice == 0) break;

            string entity = getEntityName(choice);
            if (entity == "Unknown") { cout << "Invalid choice!\n"; continue; }

            cout << "\n--- SORT " << entity << " ---\n";
            cout << "1. Sort by ID (Ascending)\n";
            cout << "2. Sort by Name/Title (Ascending)\n";
            if (choice == 1) cout << "3. Sort by Price (Ascending)\n";
            if (choice == 4) cout << "3. Sort by Booking Date (Ascending)\n";
            cout << "0. Go Back\n";
            cout << "Select sorting criteria (0-3): ";
            int subChoice;
            cin >> subChoice;

            if (subChoice == 0) continue;
            cout << "\n[Execution] Sorting " << entity << " data by criteria " << subChoice << "...\n";
        }
    }

    // ================= 5. BOUNDARY ANALYSIS (MAX/MIN) =================
    void menuBoundaryAnalysis()
    {
        while (true)
        {
            int choice = selectEntity("BOUNDARY ANALYSIS (MAX/MIN)");
            if (choice == 0) break;

            string entity = getEntityName(choice);
            if (entity == "Unknown") { cout << "Invalid choice!\n"; continue; }

            cout << "\n--- MAX/MIN ANALYSIS FOR " << entity << " ---\n";

            if (choice == 1)
            {
                Node<Tour> *maxTour = nullptr, *minTour = nullptr;
                double maxPrice = -1, minPrice = 1e12;

                Node<Tour>* current = tourService.getRepository().getHead();
                while (current != nullptr)
                {
                    if (current->data.price > maxPrice) { maxPrice = current->data.price; maxTour = current; }
                    if (current->data.price < minPrice) { minPrice = current->data.price; minTour = current; }
                    current = current->next;
                }

                cout << "\nMost Expensive Tour:\n";
                if (maxTour) cout << "  ID: " << maxTour->data.tourId << ", Price: " << maxTour->data.price << " VND\n";
                else cout << "  No tours found!\n";

                cout << "\nCheapest Tour:\n";
                if (minTour) cout << "  ID: " << minTour->data.tourId << ", Price: " << minTour->data.price << " VND\n";
                else cout << "  No tours found!\n";
            }
            else if (choice == 4)
            {
                Node<Booking> *maxBooking = nullptr, *minBooking = nullptr;
                int maxPeople = -1, minPeople = 501;

                Node<Booking>* current = bookingService.getRepository().getHead();
                while (current != nullptr)
                {
                    if (current->data.numberOfPeople > maxPeople) { maxPeople = current->data.numberOfPeople; maxBooking = current; }
                    if (current->data.numberOfPeople < minPeople) { minPeople = current->data.numberOfPeople; minBooking = current; }
                    current = current->next;
                }

                cout << "\nBooking with Most People:\n";
                if (maxBooking) cout << "  Booking ID: " << maxBooking->data.bookingId << ", People: " << maxBooking->data.numberOfPeople << "\n";
                else cout << "  No bookings found!\n";

                cout << "\nBooking with Fewest People:\n";
                if (minBooking) cout << "  Booking ID: " << minBooking->data.bookingId << ", People: " << minBooking->data.numberOfPeople << "\n";
                else cout << "  No bookings found!\n";
            }

            cout << "\n[Execution] Max/Min analysis for " << entity << " completed.\n";
        }
    }

    // ================= 6. GENERAL MEASUREMENT (SUM/AVG/COUNT) =================
    void menuGeneralMeasurement()
    {
        while (true)
        {
            int choice = selectEntity("GENERAL MEASUREMENT (SUM/AVG/COUNT)");
            if (choice == 0) break;

            string entity = getEntityName(choice);
            if (entity == "Unknown") { cout << "Invalid choice!\n"; continue; }

            cout << "\n--- MEASUREMENT FOR " << entity << " ---\n";

            if (choice == 1)
            {
                int count = tourService.getTotalTours();
                double totalPrice = 0;
                Node<Tour>* current = tourService.getRepository().getHead();
                while (current != nullptr) { totalPrice += current->data.price; current = current->next; }
                double avgPrice = (count > 0) ? totalPrice / count : 0;

                cout << "Total Tours: " << count << "\n";
                cout << "Total Price Sum: " << totalPrice << " VND\n";
                cout << "Average Price: " << avgPrice << " VND\n";
            }
            else if (choice == 2)
            {
                int count = customerService.getTotalCustomers();
                cout << "Total Customers: " << count << "\n";
            }
            else if (choice == 3)
            {
                int count = employeeService.getTotalEmployees();
                cout << "Total Employees: " << count << "\n";
            }
            else if (choice == 4)
            {
                int count = bookingService.getTotalBookings();
                double totalRevenue = bookingService.calculateTotalRevenue();
                int totalPeople = bookingService.getTotalPeopleBooked();
                double avgPeople = (count > 0) ? (double)totalPeople / count : 0;

                cout << "Total Bookings: " << count << "\n";
                cout << "Total Revenue: " << totalRevenue << " VND\n";
                cout << "Total People Booked: " << totalPeople << "\n";
                cout << "Average People per Booking: " << avgPeople << "\n";
            }

            cout << "\n[Execution] Measurement for " << entity << " completed.\n";
        }
    }

    // ================= 7. CATEGORICAL REPORTING (STATISTICS) =================
    void menuCategoricalReporting()
    {
        while (true)
        {
            int choice = selectEntity("CATEGORICAL REPORTING (STATISTICS)");
            if (choice == 0) break;

            string entity = getEntityName(choice);
            if (entity == "Unknown") { cout << "Invalid choice!\n"; continue; }

            cout << "\n--- STATISTICS FOR " << entity << " ---\n";

            if (choice == 1)
            {
                int activeCount = 0, inactiveCount = 0, completedCount = 0;
                Node<Tour>* current = tourService.getRepository().getHead();
                while (current != nullptr)
                {
                    if (current->data.status == "active") activeCount++;
                    else if (current->data.status == "inactive") inactiveCount++;
                    else if (current->data.status == "completed") completedCount++;
                    current = current->next;
                }

                cout << "Tour Statistics by Status:\n";
                cout << "  Active Tours: " << activeCount << "\n";
                cout << "  Inactive Tours: " << inactiveCount << "\n";
                cout << "  Completed Tours: " << completedCount << "\n";
            }
            else if (choice == 3)
            {
                cout << "Employee Statistics by Position:\n";
                Node<Employee>* current = employeeService.getRepository().getHead();
                while (current != nullptr)
                {
                    cout << "  " << current->data.fullName << " - " << current->data.position << "\n";
                    current = current->next;
                }
            }
            else if (choice == 4)
            {
                int pendingCount = 0, confirmedCount = 0, completedCount = 0, cancelledCount = 0;
                Node<Booking>* current = bookingService.getRepository().getHead();
                while (current != nullptr)
                {
                    if (current->data.status == "pending") pendingCount++;
                    else if (current->data.status == "confirmed") confirmedCount++;
                    else if (current->data.status == "completed") completedCount++;
                    else if (current->data.status == "cancelled") cancelledCount++;
                    current = current->next;
                }

                cout << "Booking Statistics by Status:\n";
                cout << "  Pending Bookings: " << pendingCount << "\n";
                cout << "  Confirmed Bookings: " << confirmedCount << "\n";
                cout << "  Completed Bookings: " << completedCount << "\n";
                cout << "  Cancelled Bookings: " << cancelledCount << "\n";
            }

            cout << "\n[Execution] Statistical report for " << entity << " generated.\n";
        }
    }

    // --- Helper: Lấy tên đối tượng dựa theo lựa chọn ---
    string getEntityName(int choice)
    {
        switch (choice)
        {
        case 1: return "Tour";
        case 2: return "Customer";
        case 3: return "Employee";
        case 4: return "Booking";
        default: return "Unknown";
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
    Menu(TourService &ts, CustomerService &cs, EmployeeService &es, BookingService &bs)
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
            case 1: menuMasterDataManagement(); break;
            case 2: menuUpdateInformation(); break;
            case 3: menuDataQuery(); break;
            case 4: menuDataOrganization(); break;
            case 5: menuBoundaryAnalysis(); break;
            case 6: menuGeneralMeasurement(); break;
            case 7: menuCategoricalReporting(); break;
            case 0:
            {
                cout << "\n[System] Auto-saving all data...\n";
                tourService.saveToFile("data/tours.txt");
                customerService.saveToFile("data/customers.txt");
                employeeService.saveToFile("data/employees.txt");
                bookingService.saveToFile("data/bookings.txt");
                cout << "[System] Save successful. Goodbye!\n";
                return;
            }
            default:
                cout << "Invalid choice! Please select a number from 0 to 7.\n";
            }
        }
    }
};
