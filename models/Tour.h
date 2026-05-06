// ==========================================
// File: models/Tour.h
// Description: Data model cho Tour du lịch
// ==========================================
#ifndef TOUR_H
#define TOUR_H

#include <string>

struct Tour {
    std::string tourId;
    std::string destination;
    double price;
    int maxCapacity;
    int availableSeats;
    std::string departureDate; // Format đề xuất: YYYY-MM-DD để dễ sắp xếp
    std::string status;        // "Open", "Upcoming", "Cancelled"

    // Default Constructor
    Tour() : price(0.0), maxCapacity(0), availableSeats(0), status("Open") {}

    // Parameterized Constructor
    Tour(std::string id, std::string dest, double p, int cap, std::string date)
        : tourId(id), destination(dest), price(p), maxCapacity(cap), 
          availableSeats(cap), departureDate(date), status("Open") {}
};

#endif // TOUR_H