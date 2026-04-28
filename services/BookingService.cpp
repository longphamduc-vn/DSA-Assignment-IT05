#include "BookingService.h"
#include <fstream>
#include <iostream>

BookingService::BookingService(std::string path) : filePath(path) {
    loadFromFile();
}

BookingService::~BookingService() {
    saveToFile();
}

void BookingService::loadFromFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) return;

    std::string bId, cId, tId, date; 
    int numPeople;

    while (file >> bId) {
        file >> cId >> tId;
        file.ignore(); 
        std::getline(file, date);
        file >> numPeople;
        
        this->add(Booking(bId, cId, tId, date, numPeople)); 
    }
    file.close();
}

void BookingService::saveToFile() {
    std::ofstream file(filePath);
    Node<Booking>* current = list.getHead(); 
    while (current) {
        file << current->data.getId() << "\n"    
             << current->data.getCustomerId() << "\n"
             << current->data.getTourId() << "\n"
             << current->data.getBookingDate() << "\n"
             << current->data.getNumberOfPeople() << "\n";
        current = current->next;
    }
    file.close();
}

void BookingService::findByCustomerId(const std::string& customerId) {
    Node<Booking>* current = list.getHead();
    bool found = false;
    std::cout << "\n--- Danh sach Booking cua KH: " << customerId << " ---\n";
    while (current) {
        if (current->data.getCustomerId() == customerId) {
            std::cout << current->data << "\n";
            found = true;
        }
        current = current->next;
    }
    if (!found) std::cout << "Khach hang nay chua dat tour nao!\n";
}

void BookingService::findByTourId(const std::string& tourId) {
    Node<Booking>* current = list.getHead();
    bool found = false;
    std::cout << "\n--- Danh sach Booking cua Tour: " << tourId << " ---\n";
    while (current) {
        if (current->data.getTourId() == tourId) {
            std::cout << current->data << "\n";
            found = true;
        }
        current = current->next;
    }
    if (!found) std::cout << "Tour nay chua co ai dat!\n";
}

int BookingService::getTotalPeopleBookedForTour(const std::string& tourId) {
    Node<Booking>* current = list.getHead();
    int totalPeople = 0;
    while (current) {
        if (current->data.getTourId() == tourId) {
            totalPeople += current->data.getNumberOfPeople();
        }
        current = current->next;
    }
    return totalPeople;
}