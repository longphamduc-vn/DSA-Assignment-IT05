#include "Customer.h"
#include <iomanip>

Customer::Customer() : id(""), name(""), phone(""), yearOfBirth(0) {}

Customer::Customer(std::string id, std::string name, std::string phone, int yearOfBirth)
    : id(id), name(name), phone(phone), yearOfBirth(yearOfBirth) {}

std::string Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }
int Customer::getYearOfBirth() const { return yearOfBirth; }

void Customer::setPhone(std::string newPhone) { phone = newPhone; }
void Customer::setName(std::string newName) { name = newName; }

std::ostream& operator<<(std::ostream& os, const Customer& customer) {
    os << std::setw(10) << std::left << customer.id 
       << std::setw(25) << std::left << customer.name 
       << std::setw(15) << std::left << customer.phone 
       << std::setw(10) << customer.yearOfBirth;
    return os;
}