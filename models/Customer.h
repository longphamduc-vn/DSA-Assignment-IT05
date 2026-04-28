#pragma once
#include <string>
#include <iostream>

class Customer {
private:
    std::string id;
    std::string name;
    std::string phone;
    int yearOfBirth;

public:
    Customer();
    Customer(std::string id, std::string name, std::string phone, int yearOfBirth);

    std::string getId() const;
    std::string getName() const;
    std::string getPhone() const;
    int getYearOfBirth() const;

    void setPhone(std::string newPhone);
    void setName(std::string newName);

    friend std::ostream& operator<<(std::ostream& os, const Customer& customer);
};