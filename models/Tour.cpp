#include "Tour.h"
#include <iomanip>

Tour::Tour() : id(""), name(""), price(0.0), days(0) {}

Tour::Tour(std::string id, std::string name, double price, int days) 
    : id(id), name(name), price(price), days(days) {}

std::string Tour::getId() const { return id; }
std::string Tour::getName() const { return name; }
double Tour::getPrice() const { return price; }
int Tour::getDays() const { return days; }

void Tour::setPrice(double newPrice) { price = newPrice; }

std::ostream& operator<<(std::ostream& os, const Tour& tour) {
    os << std::setw(10) << std::left << tour.id 
       << std::setw(25) << std::left << tour.name 
       << std::setw(15) << tour.price 
       << std::setw(10) << tour.days;
    return os;
}