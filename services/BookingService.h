#pragma once
#include "BaseService.h"
#include "../models/Booking.h"
#include <string>

class BookingService : public BaseService<Booking> {
private:
    std::string filePath;

public:
    BookingService(std::string path);
    ~BookingService();

    void loadFromFile() override;
    void saveToFile() override;

    void findByCustomerId(const std::string& customerId);
    void findByTourId(const std::string& tourId);
    int getTotalPeopleBookedForTour(const std::string& tourId);
};