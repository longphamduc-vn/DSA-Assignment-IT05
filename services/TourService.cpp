#include "TourService.h"
#include <fstream>
#include <iostream>

TourService::TourService(std::string path) : filePath(path) {
    loadFromFile();
}

TourService::~TourService() {
    saveToFile();
}

void TourService::loadFromFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) return;

    std::string id, name; double price; int days;
    while (file >> id) {
        file.ignore(); std::getline(file, name);
        file >> price >> days;
        
        this->add(Tour(id, name, price, days)); 
    }
    file.close();
}

void TourService::saveToFile() {
    std::ofstream file(filePath);
    Node<Tour>* current = list.getHead(); // list được kế thừa từ BaseService
    while (current) {
        file << current->data.getId() << "\n"
             << current->data.getName() << "\n"
             << current->data.getPrice() << "\n"
             << current->data.getDays() << "\n";
        current = current->next;
    }
    file.close();
}

void TourService::updatePrice(std::string id, double newPrice) {
    // Tận dụng hàm findById từ lớp cha
    Tour* tour = this->findById(id);
    if (tour) {
        tour->setPrice(newPrice);
        std::cout << "Cap nhat gia thanh cong!\n";
    } else {
        std::cout << "Khong tim thay Tour!\n";
    }
}

void TourService::sortByPriceAsc() {
    for (Node<Tour>* i = list.getHead(); i != nullptr; i = i->next) {
        for (Node<Tour>* j = i->next; j != nullptr; j = j->next) {
            if (i->data.getPrice() > j->data.getPrice()) {
                Tour temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    std::cout << "Da sap xep tang dan theo gia!\n";
}

void TourService::showMaxPriceTour() {
    if (!list.getHead()) return;
    Tour maxTour = list.getHead()->data;
    Node<Tour>* current = list.getHead()->next;
    while (current) {
        if (current->data.getPrice() > maxTour.getPrice()) {
            maxTour = current->data;
        }
        current = current->next;
    }
    std::cout << "Tour co gia cao nhat: " << maxTour << "\n";
}

void TourService::showStats() {
    std::cout << "Tong so luong Tour dang co: " << this->getSize() << "\n";
}