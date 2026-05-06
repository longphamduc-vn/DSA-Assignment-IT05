// ==========================================
// File: menu/Menu.h
// Description: Giao diện điều khiển trung tâm toàn bộ hệ thống
// ==========================================
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

#include "../services/TourService.h"
#include "../services/CustomerService.h"
#include "../services/EmployeeService.h"
#include "../services/BookingService.h"
#include "../utils/Validation.h"
#include "../utils/ConsoleUI.h"

class Menu {
private:
    TourService& tourService;
    CustomerService& customerService;
    EmployeeService& employeeService;
    BookingService& bookingService;

    // ==================================================
    // 1. YÊU CẦU 1: IN DANH SÁCH
    // ==================================================
    void printDataMenu() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "=== IN DANH SACH ===\n";
            std::cout << "1. In danh sach Tour\n";
            std::cout << "2. In danh sach Khach hang\n";
            std::cout << "3. In danh sach Booking\n";
            std::cout << "4. In danh sach Nhan vien\n";
            std::cout << "0. Quay lai\n";
            
            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: ConsoleUI::printTourTable(tourService.getRepository()); ConsoleUI::pauseScreen(); break;
                case 2: ConsoleUI::printCustomerTable(customerService.getRepository()); ConsoleUI::pauseScreen(); break;
                case 3: ConsoleUI::printBookingTable(bookingService.getRepository()); ConsoleUI::pauseScreen(); break;
                case 4: 
                    std::cout << "-> (In danh sach nhan vien...)\n"; // Tương tự ConsoleUI::printEmployeeTable
                    ConsoleUI::pauseScreen(); 
                    break;
                case 0: back = true; break;
            }
        }
    }

    // ==================================================
    // 2. YÊU CẦU 2: THÊM, SỬA, XÓA ĐỐI TƯỢNG
    // ==================================================
    void manageTours() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "--- 2.1 QUAN LY TOUR ---\n";
            std::cout << "1. Them Tour moi\n";
            std::cout << "2. Sua thong tin Tour\n";
            std::cout << "3. Cap nhat trang thai Tour\n";
            std::cout << "4. Xoa Tour\n";
            std::cout << "0. Quay lai\n";
            
            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: {
                    std::string id, dest, date;
                    std::cout << "ID Tour: "; std::getline(std::cin, id);
                    std::cout << "Diem den: "; std::getline(std::cin, dest);
                    double price = Validation::getValidDouble("Gia (VND): ");
                    int cap = Validation::getValidInteger("Suc chua toi da: ");
                    std::cout << "Ngay KH (YYYY-MM-DD): "; std::getline(std::cin, date);
                    tourService.add(Tour(id, dest, price, cap, date));
                    std::cout << "-> Them Tour thanh cong!\n";
                    break;
                }
                case 2: {
                    std::string id; std::cout << "Nhap ID Tour can sua: "; std::getline(std::cin, id);
                    Tour* t = tourService.findById(id);
                    if (t) {
                        t->price = Validation::getValidDouble("Gia moi: ");
                        t->maxCapacity = Validation::getValidInteger("Suc chua moi: ");
                        std::cout << "-> Sua thong tin thanh cong!\n";
                    } else std::cout << "-> Khong tim thay Tour!\n";
                    break;
                }
                case 3: {
                    std::string id; std::cout << "Nhap ID Tour: "; std::getline(std::cin, id);
                    Tour* t = tourService.findById(id);
                    if (t) {
                        std::cout << "Trang thai moi (Open/Upcoming/Cancelled): "; 
                        std::getline(std::cin, t->status);
                        std::cout << "-> Cap nhat trang thai thanh cong!\n";
                    }
                    break;
                }
                case 4: {
                    std::string id; std::cout << "Nhap ID Tour can xoa: "; std::getline(std::cin, id);
                    Booking* b = bookingService.getRepository().findIf([id](const Booking& bk){ return bk.tourId == id; });
                    if (b) std::cout << "-> Khong the xoa! Tour nay da co Booking.\n";
                    else if (tourService.remove(id)) std::cout << "-> Xoa Tour thanh cong!\n";
                    else std::cout << "-> Khong tim thay Tour!\n";
                    break;
                }
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    void manageCustomers() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "--- 2.2 QUAN LY KHACH HANG ---\n";
            std::cout << "1. Dang ky Khach hang moi\n";
            std::cout << "2. Cap nhat thong tin\n";
            std::cout << "3. Xoa Khach hang (Xoa mem)\n";
            std::cout << "0. Quay lai\n";
            
            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: {
                    std::string id, name, phone, email, addr;
                    std::cout << "ID Khach hang: "; std::getline(std::cin, id);
                    std::cout << "Ho ten: "; std::getline(std::cin, name);
                    std::cout << "SDT: "; std::getline(std::cin, phone);
                    std::cout << "Email: "; std::getline(std::cin, email);
                    std::cout << "Dia chi: "; std::getline(std::cin, addr);
                    customerService.add(Customer(id, Validation::normalizeName(name), phone, email, addr));
                    std::cout << "-> Dang ky thanh cong!\n";
                    break;
                }
                case 3: {
                    std::string id; std::cout << "Nhap ID Khach hang can xoa: "; std::getline(std::cin, id);
                    if (customerService.remove(id)) std::cout << "-> Da xoa mem Khach hang!\n";
                    else std::cout << "-> Khong tim thay!\n";
                    break;
                }
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    void manageBookings() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "--- 2.3 QUAN LY BOOKING ---\n";
            std::cout << "1. Tao Booking moi\n";
            std::cout << "2. Cap nhat so luong nguoi di\n";
            std::cout << "3. Doi trang thai Booking\n";
            std::cout << "4. Huy Booking\n";
            std::cout << "0. Quay lai\n";
            
            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: {
                    std::string bId, cId, tId, eId, date;
                    std::cout << "Ma Booking: "; std::getline(std::cin, bId);
                    std::cout << "Ma Khach hang: "; std::getline(std::cin, cId);
                    std::cout << "Ma Tour: "; std::getline(std::cin, tId);
                    std::cout << "Ma Nhan vien: "; std::getline(std::cin, eId);
                    std::cout << "Ngay dat (YYYY-MM-DD): "; std::getline(std::cin, date);
                    Booking b(bId, cId, tId, eId, date);
                    b.passengerCount = Validation::getValidInteger("So luong khach: ");
                    
                    if (bookingService.createBooking(b, tourService, customerService, employeeService)) {
                        std::cout << "-> Tao Booking thanh cong! Da tu dong tru cho tren Tour.\n";
                    } else std::cout << "-> Tao Booking that bai (Tour khong ton tai hoac het cho).\n";
                    break;
                }
                case 3:
                case 4: {
                    std::string id; std::cout << "Nhap Ma Booking: "; std::getline(std::cin, id);
                    std::string status = (choice == 4) ? "Cancelled" : "Confirmed"; // Giả lập
                    if (bookingService.changeBookingStatus(id, status, tourService)) {
                        std::cout << "-> Cap nhat trang thai thanh cong! Da hoan/tru cho neu can.\n";
                    } else std::cout << "-> Khong tim thay Booking!\n";
                    break;
                }
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    // ==================================================
    // 3. YÊU CẦU 3: TÌM KIẾM
    // ==================================================
    void searchMenu() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "=== TIM KIEM ===\n";
            std::cout << "1. Tim Tour theo khoang gia\n";
            std::cout << "2. Tim Tour theo ngay khoi hanh\n";
            std::cout << "3. Tim Tour theo Diem den\n";
            std::cout << "4. Tim Khach hang theo Ten hoac SDT\n";
            std::cout << "5. Tim Booking theo ma ID\n";
            std::cout << "6. Liet ke Booking cua mot Khach hang\n";
            std::cout << "0. Quay lai\n";

            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: {
                    double min = Validation::getValidDouble("Gia tu: ");
                    double max = Validation::getValidDouble("Gia den: ");
                    ConsoleUI::printTourTable(tourService.searchByPriceRange(min, max));
                    break;
                }
                case 3: {
                    std::string dest; std::cout << "Nhap diem den: "; std::getline(std::cin, dest);
                    ConsoleUI::printTourTable(tourService.searchByDestination(dest));
                    break;
                }
                case 4: {
                    std::string kw; std::cout << "Nhap Ten/SDT: "; std::getline(std::cin, kw);
                    ConsoleUI::printCustomerTable(customerService.searchByNameOrPhone(kw));
                    break;
                }
                case 6: {
                    std::string cId; std::cout << "Nhap Ma Khach hang: "; std::getline(std::cin, cId);
                    ConsoleUI::printBookingTable(bookingService.getBookingsByCustomer(cId));
                    break;
                }
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    // ==================================================
    // 4. YÊU CẦU 4: SẮP XẾP
    // ==================================================
    void sortMenu() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "=== SAP XEP ===\n";
            std::cout << "1. Tour theo Gia (Tang dan)\n";
            std::cout << "2. Tour theo Ngay khoi hanh (Gan -> Xa)\n";
            std::cout << "3. Khach hang theo Ho Ten (A-Z)\n";
            std::cout << "4. Booking theo Tong tien (Giam dan)\n";
            std::cout << "5. Booking theo Ngay dat (Moi nhat)\n";
            std::cout << "0. Quay lai\n";

            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: tourService.sortByPrice(true); std::cout << "-> Da sap xep Tour theo gia.\n"; break;
                case 2: tourService.sortByDepartureDate(); std::cout << "-> Da sap xep Tour theo ngay.\n"; break;
                case 3: customerService.sortByName(); std::cout << "-> Da sap xep Khach hang theo ten.\n"; break;
                case 4: bookingService.sortByTotalAmount(); std::cout << "-> Da sap xep Booking theo tong tien.\n"; break;
                case 5: bookingService.sortByBookingDate(); std::cout << "-> Da sap xep Booking theo ngay.\n"; break;
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    // ==================================================
    // 5. YÊU CẦU 5: TÌM MAX / MIN
    // ==================================================
    void minMaxMenu() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "=== TIM MAX / MIN ===\n";
            std::cout << "1. Tour co Gia cao nhat\n";
            std::cout << "2. Tour co Tong cho (MaxCapacity) lon nhat\n";
            std::cout << "3. Booking co Tong tien lon nhat\n";
            std::cout << "4. Nhan vien chot nhieu don nhat\n";
            std::cout << "5. Khach hang VIP chi tieu nhieu nhat\n";
            std::cout << "0. Quay lai\n";

            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: {
                    Tour* t = tourService.getMostExpensiveTour();
                    if (t) std::cout << "-> Tour max gia: " << t->destination << " - " << t->price << " VND\n";
                    break;
                }
                case 5: {
                    Customer* c = customerService.getTopVIPCustomer();
                    if (c) std::cout << "-> VIP: " << c->fullName << " - " << c->totalSpent << " VND\n";
                    break;
                }
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    // ==================================================
    // 6. YÊU CẦU 6: TÍNH TỔNG, TRUNG BÌNH, ĐẾM
    // ==================================================
    void calculateMenu() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "=== TINH TOAN & DEM ===\n";
            std::cout << "1. Tong doanh thu Booking 'Confirmed'\n";
            std::cout << "2. Gia tri trung binh 1 Tour\n";
            std::cout << "3. Trung binh so nguoi / Booking\n";
            std::cout << "4. Tong so luong Booking\n";
            std::cout << "5. Tong so Khach hang\n";
            std::cout << "6. Tong so cho con trong (AvailableSeats) tat ca Tour\n";
            std::cout << "0. Quay lai\n";

            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: std::cout << "-> Doanh thu: " << std::fixed << bookingService.calculateTotalRevenue() << " VND\n"; break;
                case 2: std::cout << "-> Gia trung binh: " << tourService.getAveragePrice() << " VND\n"; break;
                case 4: std::cout << "-> Tong Booking: " << bookingService.getRepository().getSize() << "\n"; break;
                case 5: std::cout << "-> Tong Khach: " << customerService.getRepository().getSize() << "\n"; break;
                case 6: std::cout << "-> Tong cho trong: " << tourService.countTotalAvailableSeats() << "\n"; break;
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

    // ==================================================
    // 7. YÊU CẦU 7: THỐNG KÊ CÓ ĐIỀU KIỆN
    // ==================================================
    void statisticsMenu() {
        bool back = false;
        while (!back) {
            ConsoleUI::clearScreen();
            std::cout << "=== THONG KE CO DIEU KIEN ===\n";
            std::cout << "1. Doanh thu theo thang\n";
            std::cout << "2. Danh sach Tour 'Het cho'\n";
            std::cout << "3. Ty le huy Booking\n";
            std::cout << "4. Danh sach Tour den 1 dia diem co gia < X\n";
            std::cout << "5. Danh sach Khach hang VIP (Chi tieu > X)\n";
            std::cout << "0. Quay lai\n";

            int choice = Validation::getValidInteger("Chon chuc nang: ");
            switch (choice) {
                case 1: {
                    std::string month; std::cout << "Nhap Thang (MM): "; std::getline(std::cin, month);
                    double total = 0;
                    bookingService.getRepository().forEach([&](const Booking& b) {
                        if (b.status == "Confirmed" && b.bookingDate.length() >= 7) {
                            if (b.bookingDate.substr(5, 2) == month) total += b.totalAmount;
                        }
                    });
                    std::cout << "-> Doanh thu Thang " << month << ": " << std::fixed << total << " VND\n";
                    break;
                }
                case 2: ConsoleUI::printTourTable(tourService.getSoldOutTours()); break;
                case 3: std::cout << "-> Ty le huy: " << bookingService.calculateCancellationRate() << "%\n"; break;
                case 4: {
                    std::string dest; std::cout << "Dia diem: "; std::getline(std::cin, dest);
                    double maxPrice = Validation::getValidDouble("Gia toi da: ");
                    LinkedList<Tour> res = tourService.getRepository().filter([&](const Tour& t) {
                        return t.destination.find(dest) != std::string::npos && t.price < maxPrice;
                    });
                    ConsoleUI::printTourTable(res);
                    break;
                }
                case 5: {
                    double limit = Validation::getValidDouble("Muc chi tieu VIP: ");
                    LinkedList<Customer> res = customerService.getRepository().filter([&](const Customer& c) {
                        return c.totalSpent > limit && !c.isDeleted;
                    });
                    ConsoleUI::printCustomerTable(res);
                    break;
                }
                case 0: back = true; continue;
            }
            ConsoleUI::pauseScreen();
        }
    }

public:
    Menu(TourService& ts, CustomerService& cs, EmployeeService& es, BookingService& bs)
        : tourService(ts), customerService(cs), employeeService(es), bookingService(bs) {}

    void run() {
        bool isRunning = true;
        while (isRunning) {
            ConsoleUI::clearScreen();
            std::cout << "========================================\n";
            std::cout << "  HE THONG QUAN LY DAT TOUR DU LICH\n";
            std::cout << "========================================\n";
            std::cout << "1. In va Xem Danh sach (Yeu cau 1)\n";
            std::cout << "2. Quan ly Du lieu: Them, Sua, Xoa (Yeu cau 2)\n";
            std::cout << "3. Tim kiem (Yeu cau 3)\n";
            std::cout << "4. Sap xep (Yeu cau 4)\n";
            std::cout << "5. Tim Max / Min (Yeu cau 5)\n";
            std::cout << "6. Tinh Tong, Trung binh, Dem (Yeu cau 6)\n";
            std::cout << "7. Thong ke co dieu kien (Yeu cau 7)\n";
            std::cout << "0. Thoat & Luu du lieu\n";
            
            int choice = Validation::getValidInteger("Chon chuc nang: ");
            
            switch (choice) {
                case 1: printDataMenu(); break;
                case 2: {
                    bool backMgr = false;
                    while(!backMgr) {
                        ConsoleUI::clearScreen();
                        std::cout << "=== MENU QUAN LY DU LIEU ===\n";
                        std::cout << "1. Quan ly Tour\n2. Quan ly Khach hang\n3. Quan ly Booking\n0. Quay lai\n";
                        int c = Validation::getValidInteger("Chon: ");
                        if(c == 1) manageTours();
                        else if(c == 2) manageCustomers();
                        else if(c == 3) manageBookings();
                        else if(c == 0) backMgr = true;
                    }
                    break;
                }
                case 3: searchMenu(); break;
                case 4: sortMenu(); break;
                case 5: minMaxMenu(); break;
                case 6: calculateMenu(); break;
                case 7: statisticsMenu(); break;
                case 0: 
                    std::cout << "-> Da xac nhan thoat. He thong dang ghi đe file luu tru...\n";
                    isRunning = false; 
                    break;
                default:
                    std::cout << "-> Lua chon khong hop le!\n";
                    ConsoleUI::pauseScreen();
            }
        }
    }
};

#endif // MENU_H