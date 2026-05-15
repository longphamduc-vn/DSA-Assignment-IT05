#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <sstream>

using namespace std;

struct Employee {
    string employeeId;
    string fullName;
    string position;
    string phoneNumber;
    string email;
    
    /**
     * @brief Serialize Employee to a string for file storage.
     */
    string toFileString() const {
        return employeeId + "|" + fullName + "|" + position + "|" + phoneNumber + "|" + email;
    }

    /**
     * @brief Deserialize Employee from a file string.
     */
    void fromFileString(const string& line) {
        stringstream ss(line);
        getline(ss, employeeId, '|');
        getline(ss, fullName, '|');
        getline(ss, position, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, email, '|');
    }

    /**
     * @brief Equality operator for Employee comparison.
     * @param other The other Employee to compare with.
     * @return true if all fields are equal, false otherwise.
     */
    bool operator==(const Employee& other) const
    {
        return employeeId == other.employeeId &&
               fullName == other.fullName &&
               position == other.position &&
               phoneNumber == other.phoneNumber &&
               email == other.email;
    }
    
    /**
     * @brief Inequality operator for Employee comparison.
     * @param other The other Employee to compare with.
     * @return true if any field differs, false otherwise.
     */
    bool operator!=(const Employee& other) const
    {
        return !(*this == other);
    }
};

#endif