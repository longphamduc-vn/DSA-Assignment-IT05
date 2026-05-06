// ==========================================
// File: models/Customer.h
// Description: Data model cho Khách hàng
// ==========================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

struct Customer {
    std::string customerId;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string address;
    
    // Các trường phục vụ thống kê & nghiệp vụ
    double totalSpent; // Tổng chi tiêu (để lọc Khách hàng VIP)
    bool isDeleted;    // Xóa mềm (Soft delete) để không mất lịch sử Booking

    // Default Constructor
    Customer() : totalSpent(0.0), isDeleted(false) {}

    // Parameterized Constructor
    Customer(std::string id, std::string name, std::string phone, std::string mail, std::string addr)
        : customerId(id), fullName(name), phoneNumber(phone), email(mail), address(addr), 
          totalSpent(0.0), isDeleted(false) {}
};

#endif // CUSTOMER_H