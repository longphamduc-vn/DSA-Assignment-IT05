// ==========================================
// File: main.cpp
// Description: Entry Point của chương trình
// ==========================================
#include <iostream>

#include "services/TourService.h"
#include "services/CustomerService.h"
#include "services/EmployeeService.h"
#include "services/BookingService.h"

#include "utils/FileIO.h"
#include "menu/Menu.h"

int main() {
    // 1. Khởi tạo các Service cốt lõi
    // Các service này chứa repository (Linked List) quản lý toàn bộ dữ liệu trên RAM
    TourService tourService;
    CustomerService customerService;
    EmployeeService employeeService;
    BookingService bookingService;

    // 2. Nạp dữ liệu từ File vào Memory (Data Hydration)
    std::cout << "[INFO] Dang nap du lieu tu he thong file...\n";
    FileIO::loadList<Tour>("data/tours.txt", tourService.getRepository());
    FileIO::loadList<Customer>("data/customers.txt", customerService.getRepository());
    FileIO::loadList<Employee>("data/employees.txt", employeeService.getRepository());
    FileIO::loadList<Booking>("data/bookings.txt", bookingService.getRepository());

    // 3. Khởi tạo và Chạy Vòng lặp Menu chính
    // Inject các dependency (Services) vào Menu thông qua tham chiếu
    Menu appMenu(tourService, customerService, employeeService, bookingService);
    appMenu.run();

    // 4. Lưu lại dữ liệu (Serialization) khi người dùng chọn Thoát (0)
    std::cout << "[INFO] Dang ghi đe du lieu xuong file...\n";
    FileIO::saveList<Tour>("data/tours.txt", tourService.getRepository());
    FileIO::saveList<Customer>("data/customers.txt", customerService.getRepository());
    FileIO::saveList<Employee>("data/employees.txt", employeeService.getRepository());
    FileIO::saveList<Booking>("data/bookings.txt", bookingService.getRepository());

    std::cout << "[INFO] Luu thanh cong. He thong ket thuc. Hen gap lai!\n";
    return 0;
}