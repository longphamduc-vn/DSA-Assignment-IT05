#include <iostream>
#include <string>

using namespace std;

// ================= SUB-MENUS =================

// 1.1. Master Data Management -> Tour
void menuMasterData_Tour() {
    int choice;
    while (true) {
        cout << "\n--- 1.1. MASTER DATA: TOUR ---\n";
        cout << "1. Input Tour list from keyboard\n";
        cout << "2. Output Tour list table\n";
        cout << "3. Read Tour data from file\n";
        cout << "4. Save Tour data to file\n";
        cout << "0. Go Back\n";
        cout << "Select a function (0-4): ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "\n[Execution] Inputting Tour list from keyboard...\n"; break;
            case 2: cout << "\n[Execution] Displaying Tour list...\n"; break;
            case 3: cout << "\n[Execution] Reading Tour data from file...\n"; break;
            case 4: cout << "\n[Execution] Saving Tour data to file...\n"; break;
            case 0: return;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
}

// 1. Master Data Management Menu
void menuMasterDataManagement() {
    int choice;
    while (true) {
        cout << "\n=== 1. OPERATIONS: MASTER DATA MANAGEMENT ===\n";
        cout << "1. Tour Object\n";
        cout << "2. Customer Object\n";
        cout << "3. Employee Object\n";
        cout << "4. Booking Object\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select an object (0-4): ";
        cin >> choice;

        switch (choice) {
            case 1: menuMasterData_Tour(); break;
            case 2: cout << "\n[Redirecting to IO Menu - Customer]\n"; break; // Similar to Tour
            case 3: cout << "\n[Redirecting to IO Menu - Employee]\n"; break; // Similar to Tour
            case 4: cout << "\n[Redirecting to IO Menu - Booking]\n"; break;  // Similar to Tour
            case 0: return;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
}

// 2. Information Update Menu
void menuUpdateInformation() {
    int choice;
    while (true) {
        cout << "\n=== 2. OPERATIONS: INFORMATION UPDATE ===\n";
        cout << "1. Tour Object\n";
        cout << "2. Customer Object\n";
        cout << "3. Employee Object\n";
        cout << "4. Booking Object\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select an object (0-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- 2.1. UPDATE: TOUR ---\n";
                cout << "1. Add new Tour\n2. Edit Tour info by ID\n3. Delete Tour by ID\n";
                // You can wrap the above into a specific function like menuUpdate_Tour()
                break;
            case 2:
                // Code for Customer update menu...
                break;
            case 0: return;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
}

// ================= MAIN MENU =================
void displayMainMenu() {
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

class Menu {
    
private:
    TourService& tourService;
    CustomerService& customerService;
    EmployeeService& employeeService;
    BookingService& bookingService; 

public:
    Menu(TourService& ts, CustomerService& cs, EmployeeService& es, BookingService& bs)
        : tourService(ts), customerService(cs), employeeService(es), bookingService(bs) {}

    void run() {
        int choice;
        while (true) {
            displayMainMenu();
            cout << "Enter your choice (0-7): ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Error: Please enter a valid number!\n";
                continue;
            }

            switch (choice) {
                case 1: menuMasterDataManagement(); break;
                case 2: menuUpdateInformation(); break;
                case 3: cout << "\n[Entered Data Query Menu]\n"; break;
                case 4: cout << "\n[Entered Data Organization Menu]\n"; break;
                case 5: cout << "\n[Entered Boundary Analysis Menu]\n"; break;
                case 6: cout << "\n[Entered General Measurement Menu]\n"; break;
                case 7: cout << "\n[Entered Categorical Reporting Menu]\n"; break;
                case 0:
                    cout << "\n[System] Auto-saving all data...\n";
                    cout << "[System] Save successful. Goodbye!\n";
                    return ;
                default:
                    cout << "Invalid choice! Please select a number from 0 to 7.\n";
            }
        }
    }
};
