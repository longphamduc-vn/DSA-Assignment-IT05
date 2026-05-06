// ==========================================
// File: models/Booking.h
// Description: Data model cho Đơn đặt Tour và Hành khách
// ==========================================
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "../core/LinkedList.h"

// Struct phụ thuộc: Hành khách đi kèm trong một Booking
struct Passenger {
    std::string name;
    std::string idCard; // CMND / CCCD / Passport

    Passenger() {}
    Passenger(std::string n, std::string id) : name(n), idCard(id) {}
};

struct Booking {
    std::string bookingId;
    std::string customerId;
    std::string tourId;
    std::string employeeId;
    
    int passengerCount;
    double totalAmount;
    std::string bookingDate; // Format: YYYY-MM-DD
    std::string status;      // "Pending", "Confirmed", "Cancelled"
    
    // Danh sách hành khách trong đơn vị Booking (Không dùng std::list)
    LinkedList<Passenger> passengers;

    // Default Constructor
    Booking() : passengerCount(0), totalAmount(0.0), status("Pending") {}

    // Parameterized Constructor
    Booking(std::string bId, std::string cId, std::string tId, std::string eId, std::string date)
        : bookingId(bId), customerId(cId), tourId(tId), employeeId(eId),
          passengerCount(0), totalAmount(0.0), bookingDate(date), status("Pending") {}

    // Copy Constructor (Ngăn chặn Undefined Behavior do Copy mảng động / Linked List)
    Booking(const Booking& other) {
        bookingId = other.bookingId;
        customerId = other.customerId;
        tourId = other.tourId;
        employeeId = other.employeeId;
        passengerCount = other.passengerCount;
        totalAmount = other.totalAmount;
        bookingDate = other.bookingDate;
        status = other.status;
        
        // Deep copy danh sách hành khách
        Node<Passenger>* current = other.passengers.getHead();
        while (current != nullptr) {
            passengers.addLast(current->data);
            current = current->next;
        }
    }

    // Assignment Operator
    Booking& operator=(const Booking& other) {
        if (this != &other) {
            bookingId = other.bookingId;
            customerId = other.customerId;
            tourId = other.tourId;
            employeeId = other.employeeId;
            passengerCount = other.passengerCount;
            totalAmount = other.totalAmount;
            bookingDate = other.bookingDate;
            status = other.status;

            // Xóa danh sách cũ và Deep copy danh sách mới
            passengers.clear();
            Node<Passenger>* current = other.passengers.getHead();
            while (current != nullptr) {
                passengers.addLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }
};

#endif // BOOKING_H