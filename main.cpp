// ==========================================
// File: main.cpp
// Description: Entry Point của chương trình
// ==========================================
#include <iostream>

#include "services/TourService.h"
#include "services/CustomerService.h"
#include "services/EmployeeService.h"
#include "services/BookingService.h"

#include "data/FileIO.h"
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
    FileIO::loadTours("data/tours.txt", tourService.getRepository());
    FileIO::loadCustomers("data/customers.txt", customerService.getRepository());
    FileIO::loadEmployees("data/employees.txt", employeeService.getRepository());
    FileIO::loadBookings("data/bookings.txt", bookingService.getRepository());

    // 3. Khởi tạo và Chạy Vòng lặp Menu chính
    // Inject các dependency (Services) vào Menu thông qua tham chiếu
    Menu appMenu(tourService, customerService, employeeService, bookingService);
    appMenu.run();

    // 4. Lưu lại dữ liệu (Serialization) khi người dùng chọn Thoát (0)
    std::cout << "[INFO] Dang ghi đe du lieu xuong file...\n";
    FileIO::saveTours("data/tours.txt", tourService.getRepository());
    FileIO::saveCustomers("data/customers.txt", customerService.getRepository());
    FileIO::saveEmployees("data/employees.txt", employeeService.getRepository());
    FileIO::saveBookings("data/bookings.txt", bookingService.getRepository());

    std::cout << "[INFO] Luu thanh cong. He thong ket thuc. Hen gap lai!\n";
    return 0;
}