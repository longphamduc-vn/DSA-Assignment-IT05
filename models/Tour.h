#pragma once
#include <string>
#include <iostream>

class Tour {
private:
    std::string id;
    std::string name;
    double price;
    int days;

public:
    Tour();
    Tour(std::string id, std::string name, double price, int days);

    // Getters
    std::string getId() const;
    std::string getName() const;
    double getPrice() const;
    int getDays() const;

    // Setters
    void setPrice(double newPrice);

    friend std::ostream& operator<<(std::ostream& os, const Tour& tour);
};