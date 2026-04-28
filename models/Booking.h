#pragma once
#include <string>
#include <iostream>

class Booking {
private:
    std::string bookingId;
    std::string customerId; // Khóa ngoại liên kết với Customer
    std::string tourId;     // Khóa ngoại liên kết với Tour
    std::string bookingDate;
    int numberOfPeople;

public:
    Booking();
    Booking(std::string bId, std::string cId, std::string tId, std::string date, int numPeople);

    // Getters
    std::string getId() const;
    std::string getCustomerId() const;
    std::string getTourId() const;
    std::string getBookingDate() const;
    int getNumberOfPeople() const;

    // Setters
    void setNumberOfPeople(int num);

    // Overload
    friend std::ostream& operator<<(std::ostream& os, const Booking& booking);
};