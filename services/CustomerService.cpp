#include "CustomerService.h"
#include <fstream>
#include <iostream>

CustomerService::CustomerService(std::string path) : filePath(path) {
    loadFromFile();
}

CustomerService::~CustomerService() {
    saveToFile();
}

void CustomerService::loadFromFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) return;

    std::string id, name, phone; 
    int yearOfBirth;

    while (file >> id) {
        file.ignore(); 
        std::getline(file, name);
        file >> phone >> yearOfBirth;
        
        // Dùng hàm add() của BaseService
        this->add(Customer(id, name, phone, yearOfBirth)); 
    }
    file.close();
}

void CustomerService::saveToFile() {
    std::ofstream file(filePath);
    Node<Customer>* current = list.getHead(); 
    while (current) {
        file << current->data.getId() << "\n"
             << current->data.getName() << "\n"
             << current->data.getPhone() << "\n"
             << current->data.getYearOfBirth() << "\n";
        current = current->next;
    }
    file.close();
}

void CustomerService::searchByPhone(const std::string& phone) {
    Node<Customer>* current = list.getHead();
    bool found = false;
    while (current) {
        if (current->data.getPhone() == phone) {
            std::cout << current->data << "\n";
            found = true;
        }
        current = current->next;
    }
    if (!found) std::cout << "Khong tim thay khach hang voi SDT nay!\n";
}

void CustomerService::showYoungestCustomer() {
    if (!list.getHead()) return;
    Customer youngest = list.getHead()->data;
    Node<Customer>* current = list.getHead()->next;
    
    while (current) {
        if (current->data.getYearOfBirth() > youngest.getYearOfBirth()) {
            youngest = current->data;
        }
        current = current->next;
    }
    std::cout << "Khach hang tre tuoi nhat: \n" << youngest << "\n";
}

void CustomerService::updatePhone(const std::string& id, const std::string& newPhone) {
    Customer* cus = this->findById(id); // Gọi hàm của lớp cha
    if (cus) {
        cus->setPhone(newPhone);
        std::cout << "Cap nhat so dien thoai thanh cong!\n";
    } else {
        std::cout << "Khong tim thay khach hang!\n";
    }
}