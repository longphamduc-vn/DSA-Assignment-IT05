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
};

#endif
