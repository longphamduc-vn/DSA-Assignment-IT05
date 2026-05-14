#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include <string>
#include <iostream>
#include "GenericService.h"
#include "../models/Booking.h"
#include "../core/LinkedList.h"
#include <iomanip>
/**
 * @brief Service class for managing Booking operations
 */
class BookingService : public GenericService<Booking>
{
public:
    /**
     * @brief Constructor
     */
    BookingService() {}

    /**
     * @brief Add a new booking
     * @param booking The booking object to add
     */
    void addBooking(const Booking &booking)
    {
        addItem(booking);
    }

    /**
     * @brief Search for a booking by ID
     * @param bookingId The ID to search for
     * @return Pointer to the found booking node, nullptr if not found
     */
    Node<Booking> *findBookingById(const std::string &bookingId)
    {
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.bookingId == bookingId)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /**
     * @brief Search for bookings by customer ID
     * @param customerId The customer ID to search for
     * @return LinkedList containing bookings for the specified customer
     */
    LinkedList<Booking> findBookingsByCustomerId(const std::string &customerId)
    {
        LinkedList<Booking> results;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.customer.customerId == customerId)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Search for bookings by tour ID
     * @param tourId The tour ID to search for
     * @return LinkedList containing bookings for the specified tour
     */
    LinkedList<Booking> findBookingsByTourId(const std::string &tourId)
    {
        LinkedList<Booking> results;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.tour.tourId == tourId)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Search for bookings by employee ID
     * @param employeeId The employee ID to search for
     * @return LinkedList containing bookings handled by the specified employee
     */
    LinkedList<Booking> findBookingsByEmployeeId(const std::string &employeeId)
    {
        LinkedList<Booking> results;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.employee.employeeId == employeeId)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Search for bookings by booking date
     * @param bookingDate The booking date to search for
     * @return LinkedList containing bookings on the specified date
     */
    LinkedList<Booking> findBookingsByDate(const std::string &bookingDate)
    {
        LinkedList<Booking> results;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.bookingDate == bookingDate)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Update an existing booking
     * @param bookingId The ID of booking to update
     * @param updatedBooking The updated booking data
     * @return true if update was successful, false otherwise
     */
    bool updateBooking(const std::string &bookingId, const Booking &updatedBooking)
    {
        Node<Booking> *booking = findBookingById(bookingId);
        if (booking != nullptr)
        {
            booking->data = updatedBooking;
            return true;
        }
        return false;
    }

    /**
     * @brief Get all bookings
     * @return Pointer to the head of booking list
     */
    Node<Booking> *getAllBookings()
    {
        return getAllItems();
    }

    /**
     * @brief Check if a booking exists
     * @param bookingId The ID to check
     * @return true if booking exists, false otherwise
     */
    bool bookingExists(const std::string &bookingId)
    {
        return findBookingById(bookingId) != nullptr;
    }

    /**
     * @brief Get total number of bookings
     * @return Number of bookings
     */
    int getTotalBookings()
    {
        return getItemCount();
    }

    /**
     * @brief Delete a booking by ID
     * @param bookingId The ID of the booking to delete
     * @return true if the booking was removed, false otherwise
     */
    bool deleteBooking(const std::string &bookingId)
    {
        Node<Booking> *booking = findBookingById(bookingId);
        if (booking == nullptr)
            return false;
        return dataList.remove(booking->data);
    }

    /**
     * @brief Search bookings by keyword in booking ID, customer ID, or tour ID
     * @param keyword Keyword to search for
     * @return LinkedList containing matching bookings
     */
    LinkedList<Booking> searchBookings(const std::string &keyword)
    {
        LinkedList<Booking> results;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.bookingId.find(keyword) != std::string::npos ||
                current->data.customer.customerId.find(keyword) != std::string::npos ||
                current->data.tour.tourId.find(keyword) != std::string::npos ||
                current->data.bookingDate.find(keyword) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Calculate total revenue from all bookings
     * @return Total revenue
     */
    double calculateTotalRevenue()
    {
        double totalRevenue = 0;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            totalRevenue += current->data.tour.price * current->data.numberOfPeople;
            current = current->next;
        }
        return totalRevenue;
    }

    /**
     * @brief Get the total number of people booked across all bookings
     * @return Total number of people
     */
    int getTotalPeopleBooked()
    {
        int totalPeople = 0;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            totalPeople += current->data.numberOfPeople;
            current = current->next;
        }
        return totalPeople;
    }

    /**
     * @brief Calculate total revenue from all confirmed bookings.
     * @return double Total revenue amount.
     */
    double getTotalRevenue() const
    {
        double total = 0;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            // Only count confirmed bookings towards revenue
            if (current->data.status == "confirmed")
            {
                total += (current->data.tour.price * current->data.numberOfPeople);
            }
            current = current->next;
        }
        return total;
    }

    /**
     * @brief Calculate the average spending per booking.
     * @return double Average amount spent per booking.
     */
    double getAverageSpending() const
    {
        size_t count = 0;
        double totalRevenue = 0;
        Node<Booking> *current = dataList.getHead();

        while (current != nullptr)
        {
            if (current->data.status == "confirmed")
            {
                totalRevenue += (current->data.tour.price * current->data.numberOfPeople);
                count++;
            }
            current = current->next;
        }

        return (count == 0) ? 0.0 : totalRevenue / count;
    }

    /**
     * @brief Count the total number of bookings made (excluding cancelled).
     * @return int Number of active or completed bookings.
     */
    int countBookedTours() const
    {
        int count = 0;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.status != "cancelled")
            {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    /**
     * @brief Count how many unique customers have placed at least one booking.
     * @return int Number of unique participating customers.
     */
    int countUniqueCustomers() const
    {
        LinkedList<std::string> customerIds; // Temporary list to track unique IDs
        Node<Booking> *current = dataList.getHead();

        while (current != nullptr)
        {
            if (current->data.status != "cancelled")
            {
                // Check if ID is already in our unique list
                if (!customerIds.exists(current->data.customer.customerId))
                {
                    customerIds.insert(current->data.customer.customerId, INSERT_TAIL);
                }
            }
            current = current->next;
        }
        return customerIds.getSize();
    }
    /**
     * @brief Count the number of bookings managed by a specific employee.
     * @param employeeId The ID of the employee to check.
     * @return int Total number of bookings assigned.
     */
    int getEmployeeWorkload(const std::string &employeeId) const
    {
        int count = 0;
        Node<Booking> *current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.employee.employeeId == employeeId)
            {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    /**
     * @brief Tìm đơn đặt chỗ có số lượng người tham gia lớn nhất.
     * @return Node<Booking>* Trả về con trỏ tới Node chứa Booking, hoặc nullptr nếu danh sách trống.
     */
    Node<Booking> *getBookingWithMostPeople() const
    {
        Node<Booking> *current = dataList.getHead();
        if (current == nullptr)
            return nullptr;

        Node<Booking> *extreme = current;

        while (current != nullptr)
        {
            if (current->data.numberOfPeople > extreme->data.numberOfPeople)
            {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }

    /**
     * @brief Tìm đơn đặt chỗ có số lượng người tham gia ít nhất.
     * @return Node<Booking>* Trả về con trỏ tới Node chứa Booking, hoặc nullptr nếu danh sách trống.
     */
    Node<Booking> *getBookingWithFewestPeople() const
    {
        Node<Booking> *current = dataList.getHead();
        if (current == nullptr)
            return nullptr;

        Node<Booking> *extreme = current;

        while (current != nullptr)
        {
            if (current->data.numberOfPeople < extreme->data.numberOfPeople)
            {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }

    std::map<std::string, double> getRevenueByTour() const {
        std::map<std::string, double> revenueMap;
        Node<Booking>* current = dataList.getHead();
        
        while (current) {
            std::string status = current->data.status;
            // Chuyển status về lowercase nếu cần so sánh chính xác hơn
            if (status == "confirmed" || status == "Paid" || status == "confirmed") {
                double tripCost = current->data.numberOfPeople * current->data.tour.price;
                revenueMap[current->data.tour.tourId] += tripCost;
            }
            current = current->next;
        }
        return revenueMap;
    }

    /**
     * @brief Tính giá trị trung bình đơn hàng theo trạng thái
     * Trả về map: <Status, <TotalRevenue, Count>>
     */
    std::map<std::string, std::pair<double, int>> getAverageValueByStatus() const {
        std::map<std::string, std::pair<double, int>> stats;
        Node<Booking>* current = dataList.getHead();
        
        while (current) {
            double total = current->data.numberOfPeople * current->data.tour.price;
            stats[current->data.status].first += total;
            stats[current->data.status].second++;
            current = current->next;
        }
        return stats;
    }

    /**
     * @brief Thống kê số lượng đơn theo trạng thái (Confirmed, Pending, Cancelled)
     */
    std::map<std::string, int> countBookingsByStatus() const {
        std::map<std::string, int> statusCount;
        Node<Booking>* current = dataList.getHead();
        while (current) {
            statusCount[current->data.status]++;
            current = current->next;
        }
        return statusCount;
    }

    /**
     * @brief Hiệu suất nhân viên: Đếm số đơn mỗi nhân viên phụ trách
     */
    std::map<std::string, int> getEmployeePerformance() const {
        std::map<std::string, int> perfMap;
        Node<Booking>* current = dataList.getHead();
        while (current) {
            std::string empId = current->data.employee.employeeId;
            if (!empId.empty()) {
                perfMap[empId]++;
            }
            current = current->next;
        }
        return perfMap;
    }
};

#endif
