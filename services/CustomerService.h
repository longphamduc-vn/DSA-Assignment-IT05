// ==========================================
// File: services/CustomerService.h
// Description: Nghiệp vụ quản lý Khách hàng
// ==========================================
#ifndef CUSTOMER_SERVICE_H
#define CUSTOMER_SERVICE_H

#include "GenericService.h"
#include "../models/Customer.h"

class CustomerService : public GenericService<Customer> {
public:
    // --- YÊU CẦU 2: CRUD ---
    bool update(const std::string& id, const Customer& updatedData) override {
        Customer* c = repository.findIf([id](const Customer& cust) { return cust.customerId == id && !cust.isDeleted; });
        if (c) {
            *c = updatedData;
            c->customerId = id;
            return true;
        }
        return false;
    }

    // Xóa mềm (Soft Delete)
    bool remove(const std::string& id) override {
        Customer* c = repository.findIf([id](const Customer& cust) { return cust.customerId == id; });
        if (c) {
            c->isDeleted = true;
            return true;
        }
        return false;
    }

    // Cập nhật tích lũy chi tiêu
    void addTotalSpent(const std::string& id, double amount) {
        Customer* c = repository.findIf([id](const Customer& cust) { return cust.customerId == id; });
        if (c) c->totalSpent += amount;
    }

    // --- YÊU CẦU 3 & 4: TÌM KIẾM, SẮP XẾP ---
    LinkedList<Customer> searchByNameOrPhone(const std::string& keyword) {
        return repository.filter([keyword](const Customer& c) {
            return !c.isDeleted && (c.fullName.find(keyword) != std::string::npos || c.phoneNumber == keyword);
        });
    }

    void sortByName() {
        repository.sort([](const Customer& a, const Customer& b) {
            return a.fullName < b.fullName;
        });
    }

    // --- YÊU CẦU 5: TÌM KHÁCH HÀNG VIP ---
    Customer* getTopVIPCustomer() {
        Customer* vip = nullptr;
        repository.forEach([&vip](Customer& c) {
            if (!c.isDeleted && (!vip || c.totalSpent > vip->totalSpent)) vip = &c;
        });
        return vip;
    }
};

#endif // CUSTOMER_SERVICE_H