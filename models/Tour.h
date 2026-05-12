#ifndef TOUR_H
#define TOUR_H

#include <string>
#include <sstream>

using namespace std;

struct Tour {
    string tourId;
    string tourName;
    string destination;
    double price;
    int durationDays;
    int availableSeats;
    int maxCapacity;
    string departureDate;
    string status;
    
    /**
     * @brief Serialize Tour to a string for file storage.
     */
    string toFileString() const {
        return tourId + "|" + tourName + "|" + destination + "|" + 
               to_string(price) + "|" + to_string(durationDays) + "|" + 
               to_string(availableSeats) + "|" + to_string(maxCapacity) + "|" +
               departureDate + "|" + status;
    }

    /**
     * @brief Deserialize Tour from a file string.
     */
    void fromFileString(const string& line) {
        stringstream ss(line);
        string temp;
        
        getline(ss, tourId, '|');
        getline(ss, tourName, '|');
        getline(ss, destination, '|');
        
        if (getline(ss, temp, '|')) {
            try { price = stod(temp); } catch (...) { price = 0.0; }
        }
        if (getline(ss, temp, '|')) {
            try { durationDays = stoi(temp); } catch (...) { durationDays = 0; }
        }
        if (getline(ss, temp, '|')) {
            try { availableSeats = stoi(temp); } catch (...) { availableSeats = 0; }
        }
        if (getline(ss, temp, '|')) {
            try { maxCapacity = stoi(temp); } catch (...) { maxCapacity = 0; }
        }
        if (getline(ss, departureDate, '|')) {
            // departureDate read successfully
        }
        if (getline(ss, status, '|')) {
            // status read successfully
        }
    }

    /**
     * @brief Equality operator for Tour comparison.
     */
    bool operator==(const Tour& other) const
    {
        return tourId == other.tourId &&
               tourName == other.tourName &&
               destination == other.destination &&
               price == other.price &&
               durationDays == other.durationDays &&
               availableSeats == other.availableSeats;
    }
    
    /**
     * @brief Inequality operator for Tour comparison.
     */
    bool operator!=(const Tour& other) const
    {
        return !(*this == other);
    }
};

#endif