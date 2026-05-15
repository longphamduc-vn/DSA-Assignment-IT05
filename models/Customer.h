#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>

using namespace std;

struct Customer {
    string customerId;
    string fullName;
    string phoneNumber;
    string email;
    
    /**
     * @brief Serialize Customer to a string for file storage.
     */
    string toFileString() const {
        return customerId + "|" + fullName + "|" + phoneNumber + "|" + email;
    }

    /**
     * @brief Deserialize Customer from a file string.
     */
    void fromFileString(const string& line) {
        stringstream ss(line);
        getline(ss, customerId, '|');
        getline(ss, fullName, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, email, '|');
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