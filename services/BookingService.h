#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include <string>
#include <iostream>
#include "GenericService.h"
#include "../models/Booking.h"
#include "../core/LinkedList.h"

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
    void addBooking(const Booking& booking)
    {
        addItem(booking);
    }

    /**
     * @brief Search for a booking by ID
     * @param bookingId The ID to search for
     * @return Pointer to the found booking node, nullptr if not found
     */
    Node<Booking>* findBookingById(const std::string& bookingId)
    {
        Node<Booking>* current = dataList.getHead();
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
    LinkedList<Booking> findBookingsByCustomerId(const std::string& customerId)
    {
        LinkedList<Booking> results;
        Node<Booking>* current = dataList.getHead();
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
    LinkedList<Booking> findBookingsByTourId(const std::string& tourId)
    {
        LinkedList<Booking> results;
        Node<Booking>* current = dataList.getHead();
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
    LinkedList<Booking> findBookingsByEmployeeId(const std::string& employeeId)
    {
        LinkedList<Booking> results;
        Node<Booking>* current = dataList.getHead();
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
    LinkedList<Booking> findBookingsByDate(const std::string& bookingDate)
    {
        LinkedList<Booking> results;
        Node<Booking>* current = dataList.getHead();
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
    bool updateBooking(const std::string& bookingId, const Booking& updatedBooking)
    {
        Node<Booking>* booking = findBookingById(bookingId);
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
    Node<Booking>* getAllBookings()
    {
        return getAllItems();
    }

    /**
     * @brief Check if a booking exists
     * @param bookingId The ID to check
     * @return true if booking exists, false otherwise
     */
    bool bookingExists(const std::string& bookingId)
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
     * @brief Calculate total revenue from all bookings
     * @return Total revenue
     */
    double calculateTotalRevenue()
    {
        double totalRevenue = 0;
        Node<Booking>* current = dataList.getHead();
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
        Node<Booking>* current = dataList.getHead();
        while (current != nullptr)
        {
            totalPeople += current->data.numberOfPeople;
            current = current->next;
        }
        return totalPeople;
    }
};

#endif
