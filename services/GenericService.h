#ifndef GENERIC_SERVICE_H
#define GENERIC_SERVICE_H

#include <string>
#include "../core/LinkedList.h"

/**
 * @brief Generic Service template class providing common CRUD operations
 * @tparam T The data type the service manages
 */
template <typename T>
class GenericService
{
protected:
    LinkedList<T> dataList;

public:
    /**
     * @brief Constructor
     */
    GenericService() {}

    /**
     * @brief Destructor
     */
    virtual ~GenericService() {}

    /**
     * @brief Add a new item to the list
     * @param item The item to add
     */
    virtual void addItem(T item)
    {
        dataList.insert(item, INSERT_TAIL);
    }

    /**
     * @brief Get all items from the list
     * @return Pointer to the head of the linked list
     */
    virtual Node<T>* getAllItems()
    {
        return dataList.getHead();
    }

    /**
     * @brief Get the count of items in the list
     * @return Number of items
     */
    virtual int getItemCount()
    {
        return dataList.getSize();
    }

    /**
     * @brief Check if the list is empty
     * @return true if list is empty, false otherwise
     */
    virtual bool isEmpty()
    {
        return dataList.getSize() == 0;
    }

    /**
     * @brief Clear all items from the list
     */
    virtual void clear()
    {
        dataList.clear();
    }

    /**
     * @brief Check if an item exists in the list
     * @param item The item to check for
     * @return true if item exists, false otherwise
     */
    virtual bool itemExists(T item)
    {
        return dataList.exists(item);
    }

    /**
     * @brief Access the underlying repository list
     * @return Reference to the internal linked list repository
     */
    LinkedList<T>& getRepository()
    {
        return dataList;
    }

    /**
     * @brief Access the repository in const contexts
     * @return Const reference to the internal linked list repository
     */
    const LinkedList<T>& getRepository() const
    {
        return dataList;
    }
};

#endif
