// ==========================================
// File: services/EmployeeService.h
// Description: Nghiệp vụ quản lý Nhân viên
// ==========================================
#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include "GenericService.h"
#include "../models/Employee.h"

class EmployeeService : public GenericService<Employee> {
public:
    bool update(const std::string& id, const Employee& updatedData) override {
        Employee* e = repository.findIf([id](const Employee& emp) { return emp.employeeId == id; });
        if (e) {
            *e = updatedData;
            e->employeeId = id;
            return true;
        }
        return false;
    }

    bool remove(const std::string& id) override {
        return repository.removeIf([id](const Employee& e) { return e.employeeId == id; });
    }

    void addSale(const std::string& id, double amount) {
        Employee* e = repository.findIf([id](const Employee& emp) { return emp.employeeId == id; });
        if (e) {
            e->bookingCount++;
            e->totalSales += amount;
        }
    }

    void sortByPositionAndName() {
        repository.sort([](const Employee& a, const Employee& b) {
            if (a.position == b.position) return a.fullName < b.fullName;
            return a.position < b.position;
        });
    }

    Employee* getBestEmployee() {
        Employee* best = nullptr;
        repository.forEach([&best](Employee& e) {
            if (!best || e.bookingCount > best->bookingCount) best = &e;
        });
        return best;
    }
};

#endif // EMPLOYEE_SERVICE_H