#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <sstream>

struct Employee {
    std::string employeeId;
    std::string fullName;
    std::string position;
    std::string phoneNumber;
    std::string email;
    
    /**
     * @brief Serialize Employee to a string for file storage.
     */
    std::string toFileString() const {
        return employeeId + "|" + fullName + "|" + position + "|" + phoneNumber + "|" + email;
    }

    /**
     * @brief Deserialize Employee from a file string.
     */
    void fromFileString(const std::string& line) {
        std::stringstream ss(line);
        std::getline(ss, employeeId, '|');
        std::getline(ss, fullName, '|');
        std::getline(ss, position, '|');
        std::getline(ss, phoneNumber, '|');
        std::getline(ss, email, '|');
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