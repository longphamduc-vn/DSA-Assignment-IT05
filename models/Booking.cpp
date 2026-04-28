#include "Booking.h"
#include <iomanip>

Booking::Booking() : bookingId(""), customerId(""), tourId(""), bookingDate(""), numberOfPeople(0) {}

Booking::Booking(std::string bId, std::string cId, std::string tId, std::string date, int numPeople)
    : bookingId(bId), customerId(cId), tourId(tId), bookingDate(date), numberOfPeople(numPeople) {}

std::string Booking::getId() const { return bookingId; }
std::string Booking::getCustomerId() const { return customerId; }
std::string Booking::getTourId() const { return tourId; }
std::string Booking::getBookingDate() const { return bookingDate; }
int Booking::getNumberOfPeople() const { return numberOfPeople; }

void Booking::setNumberOfPeople(int num) { numberOfPeople = num; }

std::ostream& operator<<(std::ostream& os, const Booking& booking) {
    os << std::setw(10) << std::left << booking.bookingId 
       << std::setw(15) << std::left << booking.customerId 
       << std::setw(15) << std::left << booking.tourId 
       << std::setw(15) << std::left << booking.bookingDate 
       << std::setw(10) << booking.numberOfPeople;
    return os;
}