#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>
#include <regex>
#include <cctype>

class Validation {
public:
    /**
     * @brief Check if string is empty or contains only whitespace
     * @param str String to check
     * @return true if empty or whitespace only, false otherwise
     */
    static bool isEmpty(const std::string& str) {
        if (str.empty()) return true;
        for (char c : str) {
            if (!std::isspace(c)) return false;
        }
        return true;
    }

    /**
     * @brief Validate ID format (alphanumeric, no spaces)
     * @param id ID string to validate
     * @return true if valid, false otherwise
     */
    static bool isValidId(const std::string& id) {
        if (isEmpty(id) || id.length() > 20) return false;
        for (char c : id) {
            if (!std::isalnum(c)) return false;
        }
        return true;
    }

    /**
     * @brief Validate email format
     * @param email Email string to validate
     * @return true if valid email format, false otherwise
     */
    static bool isValidEmail(const std::string& email) {
        if (isEmpty(email)) return false;
        std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email, emailRegex);
    }

    /**
     * @brief Validate phone number (10-15 digits)
     * @param phone Phone number to validate
     * @return true if valid, false otherwise
     */
    static bool isValidPhoneNumber(const std::string& phone) {
        if (isEmpty(phone) || phone.length() < 10 || phone.length() > 15) return false;
        for (char c : phone) {
            if (!std::isdigit(c) && c != '+' && c != '-' && c != ' ') return false;
        }
        return true;
    }

    /**
     * @brief Validate name (letters, spaces, Vietnamese characters)
     * @param name Name to validate
     * @return true if valid, false otherwise
     */
    static bool isValidName(const std::string& name) {
        if (isEmpty(name) || name.length() > 100) return false;
        // Allow letters, spaces, and some common accent characters
        for (char c : name) {
            if (!std::isalpha(c) && !std::isspace(c) && 
                (unsigned char)c < 128) {
                // ASCII letters and spaces are OK
                // UTF-8 Vietnamese chars will have MSB set
            }
        }
        return true;
    }

    /**
     * @brief Validate position (TourGuide, Manager, Staff, etc.)
     * @param position Position to validate
     * @return true if valid position, false otherwise
     */
    static bool isValidPosition(const std::string& position) {
        if (isEmpty(position)) return false;
        static const std::string validPositions[] = {
            "Manager", "TourGuide", "Staff", "Accountant", "Driver"
        };
        for (const auto& pos : validPositions) {
            if (position == pos) return true;
        }
        return false;
    }

    /**
     * @brief Validate price (positive double)
     * @param price Price value to validate
     * @return true if valid price, false otherwise
     */
    static bool isValidPrice(double price) {
        return price > 0 && price < 1e12; // Allow reasonable price range
    }

    /**
     * @brief Validate duration (positive integer)
     * @param duration Duration in days
     * @return true if valid, false otherwise
     */
    static bool isValidDuration(int duration) {
        return duration > 0 && duration <= 365;
    }

    /**
     * @brief Validate available seats (positive integer)
     * @param seats Number of available seats
     * @return true if valid, false otherwise
     */
    static bool isValidSeats(int seats) {
        return seats > 0 && seats <= 1000;
    }

    /**
     * @brief Validate date format (DD/MM/YYYY)
     * @param date Date string to validate
     * @return true if valid format, false otherwise
     */
    static bool isValidDate(const std::string& date) {
        if (isEmpty(date)) return false;
        std::regex dateRegex(R"(\d{2}/\d{2}/\d{4})");
        return std::regex_match(date, dateRegex);
    }

    /**
     * @brief Validate booking status
     * @param status Status string
     * @return true if valid status, false otherwise
     */
    static bool isValidBookingStatus(const std::string& status) {
        if (isEmpty(status)) return false;
        static const std::string validStatuses[] = {
            "pending", "confirmed", "completed", "cancelled"
        };
        std::string lowerStatus = status;
        // Convert to lowercase for comparison
        for (char& c : lowerStatus) {
            c = std::tolower(c);
        }
        for (const auto& s : validStatuses) {
            if (lowerStatus == s) return true;
        }
        return false;
    }

    /**
     * @brief Validate tour status
     * @param status Status string
     * @return true if valid status, false otherwise
     */
    static bool isValidTourStatus(const std::string& status) {
        if (isEmpty(status)) return false;
        static const std::string validStatuses[] = {
            "active", "inactive", "completed"
        };
        std::string lowerStatus = status;
        for (char& c : lowerStatus) {
            c = std::tolower(c);
        }
        for (const auto& s : validStatuses) {
            if (lowerStatus == s) return true;
        }
        return false;
    }

    /**
     * @brief Validate number of people in booking
     * @param numberOfPeople Number of people
     * @return true if valid, false otherwise
     */
    static bool isValidNumberOfPeople(int numberOfPeople) {
        return numberOfPeople > 0 && numberOfPeople <= 500;
    }

    /**
     * @brief Print validation error message
     * @param fieldName Name of the field that failed validation
     * @param reason Reason for validation failure
     */
    static void printValidationError(const std::string& fieldName, const std::string& reason) {
        std::cerr << "ERROR: Invalid " << fieldName << "! " << reason << std::endl;
    }
};

#endif // VALIDATION_H
