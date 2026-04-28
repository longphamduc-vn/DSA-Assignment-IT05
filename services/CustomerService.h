#pragma once
#include "BaseService.h"
#include "../models/Customer.h"
#include <string>

class CustomerService : public BaseService<Customer> {
private:
    std::string filePath;

public:
    CustomerService(std::string path);
    ~CustomerService();

    void loadFromFile() override;
    void saveToFile() override;

    void searchByPhone(const std::string& phone);
    void showYoungestCustomer();
    void updatePhone(const std::string& id, const std::string& newPhone);
};