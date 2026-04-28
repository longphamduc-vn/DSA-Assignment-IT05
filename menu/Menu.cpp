#include "Menu.h"
#include "../utils/Validator.h"
#include <iostream>

Menu::Menu() : tourService("data/tours.txt") {}

void Menu::showTourMenu() {
    int choice;
    do {
        std::cout << "\n=== QUAN LY TOUR ===\n";
        std::cout << "1. Them Tour\n";
        std::cout << "2. Hien thi danh sach\n";
        std::cout << "3. Tim kiem theo Ma\n";
        std::cout << "4. Sap xep theo Gia\n";
        std::cout << "5. Thong ke co ban\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string id, name; double price; int days;
                std::cout << "Ma: "; std::cin >> id;
                Validator::clearInputBuffer();
                std::cout << "Ten: "; std::getline(std::cin, name);
                std::cout << "Gia: "; std::cin >> price;
                std::cout << "So ngay: "; std::cin >> days;
                
                // SỬA LỖI 1: Gọi hàm add() từ BaseService
                tourService.add(Tour(id, name, price, days));
                std::cout << "Them tour thanh cong!\n";
                break;
            }
            case 2: 
                // Gọi hàm displayAll() từ BaseService
                tourService.displayAll(); 
                break;
            case 3: {
                std::string id; std::cout << "Nhap ma: "; std::cin >> id;
                
                // SỬA LỖI 2: Gọi findById() và xử lý con trỏ
                Tour* tour = tourService.findById(id);
                if (tour != nullptr) {
                    std::cout << "Tim thay: " << *tour << "\n";
                } else {
                    std::cout << "Khong tim thay Tour co ma " << id << "!\n";
                }
                break;
            }
            case 4: 
                tourService.sortByPriceAsc(); 
                break;
            case 5: 
                tourService.showStats(); 
                tourService.showMaxPriceTour();
                break;
            case 0: break;
            default: std::cout << "Khong hop le!\n";
        }
    } while (choice != 0);
}

void Menu::run() {
    int choice;
    do {
        std::cout << "\n=== HE THONG QUAN LY DAT TOUR ===\n";
        std::cout << "1. Quan ly Tour\n";
        std::cout << "2. Quan ly Khach Hang \n";
        std::cout << "3. Quan ly Dat Tour \n";
        std::cout << "0. Luu du lieu va Thoat\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        if (choice == 1) showTourMenu();
        else if (choice == 0) std::cout << "Tam biet!\n";
        else std::cout << "Chuc nang dang hoan thien tren Menu!\n";
        
    } while (choice != 0);
}