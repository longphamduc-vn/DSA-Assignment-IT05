#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cstddef>
#include "Node.h"

using namespace std;
/**
 * @brief Enum to define where a new element should be placed in the list.
 */
typedef enum
{
    INSERT_HEAD,   // Add node at the beginning of the list
    INSERT_TAIL,   // Add node at the end of the list
    INSERT_AFTER   // Add node after a specific existing node
} InsertMode;

/**
 * @brief A generic Singly Linked List class template.
 * @tparam T The type of data stored in the list.
 */
template <typename T>
class LinkedList
{
private:
    Node<T> *head; // Pointer to the first node in the list

public:
    /**
     * @brief Constructor: Initializes an empty linked list.
     */
    LinkedList() : head(nullptr) {}

    /**
     * @brief Inserts a new element into the list based on the specified mode.
     * @param data The value to be stored in the new node.
     * @param mode The insertion strategy (HEAD, TAIL, or AFTER).
     * @param afterNode Reference node for INSERT_AFTER mode (default is nullptr).
     */
    void insert(T data, InsertMode mode, Node<T> *afterNode = nullptr)
    {
        // Allocate memory for the new node
        Node<T> *newNode = new Node<T>(data);

        switch (mode)
        {
        case INSERT_HEAD:
            newNode->next = head;
            head = newNode;
            break;

        case INSERT_TAIL:
            if (head == nullptr) // List is empty
            {
                head = newNode;
            }
            else
            {
                Node<T> *lastNode = head;
                // Traverse until the last node is reached
                while (lastNode->next != nullptr)
                {
                    lastNode = lastNode->next;
                }
                lastNode->next = newNode;
            }
            break;

        case INSERT_AFTER:
            if (afterNode != nullptr)
            {
                newNode->next = afterNode->next;
                afterNode->next = newNode;
            }
            else
            {
                // Clean up memory if no valid reference node is provided
                delete newNode;
            }
            break;
        }
    }

    /**
     * @brief Returns a pointer to the head node of the list.
     * @return Node<T>* Pointer to the head node or nullptr if list is empty.
     */
    Node<T>* getHead() const
    {
        return head;
    }


    /**
     * @brief Checks if a value exists in the list.
     * @param value The value to look for.
     * @return true if the value exists, false otherwise.
     */
    bool exists(T value) const
    {
        return search(value) != nullptr;
    }

    /**
     * @brief Searches for the first occurrence of a value.
     * @param value The value to look for.
     * @return Node<T>* Pointer to the node if found, otherwise nullptr.
     */
    Node<T>* search(T value) const
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    /**
     * @brief Removes the first node containing the specified value.
     * @param value The value to be deleted.
     * @return true if an element was removed, false otherwise.
     */
    bool remove(T value)
    {
        if (head == nullptr) return false;

        // Handle deletion at the head specifically
        if (head->data == value)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node<T> *current = head;
        // Search for the node preceding the one to be deleted
        while (current->next != nullptr && current->next->data != value)
        {
            current = current->next;
        }

        if (current->next != nullptr)
        {
            Node<T> *targetNode = current->next;
            current->next = targetNode->next; // Bypass the target node
            delete targetNode;                // Free memory
            return true;
        }

        return false;
    }

    

    /**
     * @brief Retrieves the element at a specific index.
     * @param index The position of the element (0-based).
     * @return T The value at the specified index.
     * @throw out_of_range if index is out of bounds.
     */
    T getAt(size_t index) const
    {
        Node<T> *current = head;
        size_t count = 0;
        while (current != nullptr && count < index)
        {
            current = current->next;
            count++;
        }
        if (current == nullptr)
        {
            throw out_of_range("Index out of bounds");
        }
        return current->data;
    }

    /**
     * @brief Calculates the total number of elements in the list.
     * @return size_t The current size of the list.
     */
    size_t getSize() const
    {
        size_t count = 0;
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    /**
     * @brief Clears all elements from the list.
     */
    void clear()
    {
        while (head != nullptr)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    /**
     * @brief Destructor: Ensures all dynamically allocated nodes are deleted.
     */
    ~LinkedList()
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            Node<T> *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    /**
     * @brief Tìm giá trị nhỏ nhất trong danh sách.
     * @return T Giá trị nhỏ nhất.
     * @throw runtime_error Nếu danh sách trống.
     */
    T getMin() const
    {
        if (head == nullptr)
        {
            throw runtime_error("List is empty");
        }

        Node<T> *current = head;
        T minVal = head->data;

        while (current != nullptr)
        {
            if (current->data < minVal)
            {
                minVal = current->data;
            }
            current = current->next;
        }
        return minVal;
    }

    /**
     * @brief Tìm giá trị lớn nhất trong danh sách.
     * @return T Giá trị lớn nhất.
     * @throw runtime_error Nếu danh sách trống.
     */
    T getMax() const
    {
        if (head == nullptr)
        {
            throw runtime_error("List is empty");
        }

        Node<T> *current = head;
        T maxVal = head->data;

        while (current != nullptr)
        {
            if (current->data > maxVal)
            {
                maxVal = current->data;
            }
            current = current->next;
        }
        return maxVal;
    }
};

#endif