#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>

struct Customer {
    std::string customerId;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    
    /**
     * @brief Serialize Customer to a string for file storage.
     */
    std::string toFileString() const {
        return customerId + "|" + fullName + "|" + phoneNumber + "|" + email;
    }

    /**
     * @brief Deserialize Customer from a file string.
     */
    void fromFileString(const std::string& line) {
        std::stringstream ss(line);
        std::getline(ss, customerId, '|');
        std::getline(ss, fullName, '|');
        std::getline(ss, phoneNumber, '|');
        std::getline(ss, email, '|');
    }

    /**
     * @brief Equality operator for Customer comparison.
     */
    bool operator==(const Customer& other) const
    {
        return customerId == other.customerId &&
               fullName == other.fullName &&
               phoneNumber == other.phoneNumber &&
               email == other.email;
    }
    
    /**
     * @brief Inequality operator for Customer comparison.
     */
    bool operator!=(const Customer& other) const
    {
        return !(*this == other);
    }
};

#endif