#ifndef TOUR_H
#define TOUR_H

#include <string>
#include <sstream>

struct Tour {
    std::string tourId;
    std::string tourName;
    std::string destination;
    double price;
    int durationDays;
    int availableSeats;
    
    /**
     * @brief Serialize Tour to a string for file storage.
     */
    std::string toFileString() const {
        return tourId + "|" + tourName + "|" + destination + "|" + 
               std::to_string(price) + "|" + std::to_string(durationDays) + "|" + 
               std::to_string(availableSeats);
    }

    /**
     * @brief Deserialize Tour from a file string.
     */
    void fromFileString(const std::string& line) {
        std::stringstream ss(line);
        std::string temp;
        
        std::getline(ss, tourId, '|');
        std::getline(ss, tourName, '|');
        std::getline(ss, destination, '|');
        
        if (std::getline(ss, temp, '|')) {
            try { price = std::stod(temp); } catch (...) { price = 0.0; }
        }
        if (std::getline(ss, temp, '|')) {
            try { durationDays = std::stoi(temp); } catch (...) { durationDays = 0; }
        }
        if (std::getline(ss, temp, '|')) {
            try { availableSeats = std::stoi(temp); } catch (...) { availableSeats = 0; }
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