// ==========================================
// File: models/Employee.h
// Description: Data model cho Nhân viên tư vấn
// ==========================================
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

struct Employee {
    std::string employeeId;
    std::string fullName;
    std::string position;
    
    
    int bookingCount;     // Tổng số đơn đã chốt
    double totalSales;    // Tổng doanh thu mang lại

    // Default Constructor
    Employee() : bookingCount(0), totalSales(0.0) {}

    // Parameterized Constructor
    Employee(std::string id, std::string name, std::string pos)
        : employeeId(id), fullName(name), position(pos), bookingCount(0), totalSales(0.0) {}
};

#endif // EMPLOYEE_H