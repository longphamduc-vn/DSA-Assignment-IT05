#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <sstream>
#include "Customer.h"
#include "Tour.h"
#include "Employee.h"
using namespace std;

struct Booking {
    string bookingId;
    string bookingDate;
    int numberOfPeople;
    string status;  // confirmed, cancelled, pending

    Customer customer;
    Tour tour;
    Employee employee;
    
    /**
     * @brief Serialize Booking to a string for file storage.
     * Note: Only stores IDs of the nested objects to prevent data duplication.
     */
    string toFileString() const {
        return bookingId + "|" + bookingDate + "|" + 
               to_string(numberOfPeople) + "|" + status + "|" + 
               customer.customerId + "|" + tour.tourId + "|" + employee.employeeId;
    }

    /**
     * @brief Deserialize Booking from a file string.
     * Note: Only recovers the IDs of the nested objects. Full objects should be 
     * reconstructed by a service/manager class later if needed.
     */
    void fromFileString(const string& line) {
        stringstream ss(line);
        string temp;
        
        getline(ss, bookingId, '|');
        getline(ss, bookingDate, '|');
        
        if (getline(ss, temp, '|')) {
            try { numberOfPeople = stoi(temp); } catch (...) { numberOfPeople = 0; }
        }
        
        getline(ss, status, '|');
        
        // Read mapping IDs into the nested objects
        getline(ss, customer.customerId, '|');
        getline(ss, tour.tourId, '|');
        getline(ss, employee.employeeId, '|');
    }

    /**
     * @brief Equality operator for Booking comparison.
     */
    bool operator==(const Booking& other) const
    {
        return bookingId == other.bookingId &&
               bookingDate == other.bookingDate &&
               numberOfPeople == other.numberOfPeople &&
               status == other.status &&
               customer == other.customer &&
               tour == other.tour &&
               employee == other.employee;
    }
    
    /**
     * @brief Inequality operator for Booking comparison.
     */
    bool operator!=(const Booking& other) const
    {
        return !(*this == other);
    }
};

#endif