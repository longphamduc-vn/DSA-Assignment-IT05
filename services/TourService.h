#ifndef TOUR_SERVICE_H
#define TOUR_SERVICE_H

#include <string>
#include <iostream>
#include "GenericService.h"
#include "../models/Tour.h"
#include "../core/LinkedList.h"

/**
 * @brief Service class for managing Tour operations
 */
class TourService : public GenericService<Tour>
{
public:
    struct CountResult {
        std::string key;
        int count;
    };

    /**
     * @brief Constructor
     */
    TourService() {}

    /**
     * @brief Add a new tour
     * @param tour The tour object to add
     */
    void addTour(const Tour& tour)
    {
        addItem(tour);
    }

    /**
     * @brief Search for a tour by ID
     * @param tourId The ID to search for
     * @return Pointer to the found tour node, nullptr if not found
     */
    Node<Tour>* findTourById(const std::string& tourId)
    {
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.tourId == tourId)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /**
     * @brief Search for tours by destination (partial match)
     * @param destination The destination to search for
     * @return LinkedList containing matching tours
     */
    LinkedList<Tour> findTourByDestination(const std::string& destination)
    {
        LinkedList<Tour> results;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.destination.find(destination) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Search for tours by name
     * @param tourName The tour name to search for
     * @return LinkedList containing matching tours
     */
    LinkedList<Tour> findTourByName(const std::string& tourName)
    {
        LinkedList<Tour> results;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.tourName.find(tourName) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Find tours within a price range
     * @param minPrice The minimum price
     * @param maxPrice The maximum price
     * @return LinkedList containing tours within the price range
     */
    LinkedList<Tour> findTourByPriceRange(double minPrice, double maxPrice)
    {
        LinkedList<Tour> results;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.price >= minPrice && current->data.price <= maxPrice)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Update an existing tour
     * @param tourId The ID of tour to update
     * @param updatedTour The updated tour data
     * @return true if update was successful, false otherwise
     */
    bool updateTour(const std::string& tourId, const Tour& updatedTour)
    {
        Node<Tour>* tour = findTourById(tourId);
        if (tour != nullptr)
        {
            tour->data = updatedTour;
            return true;
        }
        return false;
    }

    /**
     * @brief Get all tours
     * @return Pointer to the head of tour list
     */
    Node<Tour>* getAllTours()
    {
        return getAllItems();
    }

    /**
     * @brief Check if a tour exists
     * @param tourId The ID to check
     * @return true if tour exists, false otherwise
     */
    bool tourExists(const std::string& tourId)
    {
        return findTourById(tourId) != nullptr;
    }

    /**
     * @brief Get total number of tours
     * @return Number of tours
     */
    int getTotalTours()
    {
        return getItemCount();
    }

    /**
     * @brief Delete a tour by ID
     * @param tourId The ID of the tour to delete
     * @return true if the tour was removed, false otherwise
     */
    bool deleteTour(const std::string& tourId)
    {
        Node<Tour>* tourNode = findTourById(tourId);
        if (tourNode == nullptr) return false;
        return dataList.remove(tourNode->data);
    }

    // ==========================================
    // CÁC HÀM SẮP XẾP (SORTING) CHO MENU
    // ==========================================

    /**
     * @brief Sort tours by ID
     * @param ascending true for A-Z, false for Z-A
     */
    void sortToursById(bool ascending = true)
    {
        if (dataList.getHead() == nullptr || dataList.getHead()->next == nullptr) return;

        bool swapped;
        do {
            swapped = false;
            Node<Tour>* current = dataList.getHead();
            while (current->next != nullptr) {
                bool condition = ascending ? (current->data.tourId > current->next->data.tourId) 
                                           : (current->data.tourId < current->next->data.tourId);
                if (condition) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    /**
     * @brief Sort tours by Name
     * @param ascending true for A-Z, false for Z-A
     */
    void sortToursByName(bool ascending = true)
    {
        if (dataList.getHead() == nullptr || dataList.getHead()->next == nullptr) return;

        bool swapped;
        do {
            swapped = false;
            Node<Tour>* current = dataList.getHead();
            while (current->next != nullptr) {
                bool condition = ascending ? (current->data.tourName > current->next->data.tourName) 
                                           : (current->data.tourName < current->next->data.tourName);
                if (condition) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    /**
     * @brief Sort tours by Price
     * @param ascending true for Lowest to Highest, false for Highest to Lowest
     */
    void sortToursByPrice(bool ascending = true)
    {
        if (dataList.getHead() == nullptr || dataList.getHead()->next == nullptr) return;

        bool swapped;
        do {
            swapped = false;
            Node<Tour>* current = dataList.getHead();
            while (current->next != nullptr) {
                bool condition = ascending ? (current->data.price > current->next->data.price) 
                                           : (current->data.price < current->next->data.price);
                if (condition) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    /**
     * @brief Search tours by keyword in ID, name, or destination
     * @param keyword Keyword to search for
     * @return LinkedList containing matching tours
     */
    LinkedList<Tour> searchTours(const std::string& keyword)
    {
        LinkedList<Tour> results;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.tourId.find(keyword) != std::string::npos ||
                current->data.tourName.find(keyword) != std::string::npos ||
                current->data.destination.find(keyword) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

/**
     * @brief Tìm tour có giá cao nhất. Trả về Node chứa tour đó.
     */
    Node<Tour>* getHighestPriceTour() const {
        Node<Tour>* current = dataList.getHead();
        if (current == nullptr) return nullptr; // Trả về nullptr thay vì throw để UI dễ xử lý

        Node<Tour>* extreme = current;

        while (current != nullptr) {
            if (current->data.price > extreme->data.price) {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }

    /**
     * @brief Tìm tour có giá thấp nhất.
     */
    Node<Tour>* getLowestPriceTour() const {
        Node<Tour>* current = dataList.getHead();
        if (current == nullptr) return nullptr;

        Node<Tour>* extreme = current;

        while (current != nullptr) {
            if (current->data.price < extreme->data.price) {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }
    

    /**
     * @brief Tìm tour có thời gian dài nhất.
     */
    Node<Tour>* getLongestDurationTour() const {
        Node<Tour>* current = dataList.getHead();
        if (current == nullptr) return nullptr;

        Node<Tour>* extreme = current;

        while (current != nullptr) {
            if (current->data.durationDays > extreme->data.durationDays) {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }

    /**
     * @brief Tìm tour có thời gian ngắn nhất.
     */
    Node<Tour>* getShortestDurationTour() const {
        Node<Tour>* current = dataList.getHead();
        if (current == nullptr) return nullptr;

        Node<Tour>* extreme = current;

        while (current != nullptr) {
            if (current->data.durationDays < extreme->data.durationDays) {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }

    /**
     * @brief Tìm tour phổ biến nhất (nhiều khách đăng ký nhất).
     */
    Node<Tour>* getMostPopularTour() const {
        Node<Tour>* current = dataList.getHead();
        if (current == nullptr) return nullptr;

        Node<Tour>* extreme = current;

        while (current != nullptr) {
            int currentBooked = current->data.maxCapacity - current->data.availableSeats;
            int extremeBooked = extreme->data.maxCapacity - extreme->data.availableSeats;
            
            if (currentBooked > extremeBooked) {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }

    /**
     * @brief Tìm tour ít phổ biến nhất.
     */
    Node<Tour>* getLeastPopularTour() const {
        Node<Tour>* current = dataList.getHead();
        if (current == nullptr) return nullptr;

        Node<Tour>* extreme = current;

        while (current != nullptr) {
            int currentBooked = current->data.maxCapacity - current->data.availableSeats;
            int extremeBooked = extreme->data.maxCapacity - extreme->data.availableSeats;

            if (currentBooked < extremeBooked) {
                extreme = current;
            }
            current = current->next;
        }
        return extreme;
    }
    /**
     * @brief Thống kê số lượng Tour theo địa điểm
     */
    LinkedList<CountResult> countToursByDestination() const {
        LinkedList<CountResult> destCount;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr) {
            const std::string& dest = current->data.destination;
            Node<CountResult>* entry = destCount.getHead();
            while (entry != nullptr && entry->data.key != dest) {
                entry = entry->next;
            }
            if (entry != nullptr) {
                entry->data.count++;
            } else {
                destCount.insert(CountResult{dest, 1}, INSERT_TAIL);
            }
            current = current->next;
        }
        return destCount;
    }

    /**
     * @brief Đếm số lượng Tour trong khoảng giá
     */
    int countToursInPriceRange(double minPrice, double maxPrice) const {
        int count = 0;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr) {
            if (current->data.price >= minPrice && current->data.price <= maxPrice) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    /**
     * @brief Thống kê số lượng Tour theo trạng thái
     */
    LinkedList<CountResult> countToursByStatus() const {
        LinkedList<CountResult> statusCount;
        Node<Tour>* current = dataList.getHead();
        while (current != nullptr) {
            const std::string& status = current->data.status;
            Node<CountResult>* entry = statusCount.getHead();
            while (entry != nullptr && entry->data.key != status) {
                entry = entry->next;
            }
            if (entry != nullptr) {
                entry->data.count++;
            } else {
                statusCount.insert(CountResult{status, 1}, INSERT_TAIL);
            }
            current = current->next;
        }
        return statusCount;
    }
};

#endif
