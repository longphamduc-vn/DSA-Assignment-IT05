#ifndef CUSTOMER_SERVICE_H
#define CUSTOMER_SERVICE_H

#include <string>
#include <iostream>
#include "GenericService.h"
#include "../models/Customer.h"
#include "../core/LinkedList.h"

/**
 * @brief Service class for managing Customer operations
 */
class CustomerService : public GenericService<Customer>
{
public:
    /**
     * @brief Constructor
     */
    CustomerService() {}

    /**
     * @brief Add a new customer
     * @param customer The customer object to add
     */
    bool addCustomer(const Customer& customer)
    {
        if (customerExists(customer.customerId))
        {
            return false; 
        }

        addItem(customer);
        return true; 
    }

    /**
     * @brief Search for a customer by ID
     * @param customerId The ID to search for
     * @return Pointer to the found customer node, nullptr if not found
     */
    Node<Customer>* findCustomerById(const std::string& customerId)
    {
        Node<Customer>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.customerId == customerId)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /**
     * @brief Search for customers by name (partial match)
     * @param name The name to search for
     * @return LinkedList containing matching customers
     */
    LinkedList<Customer> findCustomerByName(const std::string& name)
    {
        LinkedList<Customer> results;
        Node<Customer>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.fullName.find(name) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Update an existing customer
     * @param customerId The ID of customer to update
     * @param updatedCustomer The updated customer data
     * @return true if update was successful, false otherwise
     */
    bool updateCustomer(const std::string& customerId, const Customer& updatedCustomer)
    {
        Node<Customer>* customer = findCustomerById(customerId);
        if (customer != nullptr)
        {
            customer->data = updatedCustomer;
            return true;
        }
        return false;
    }

    /**
     * @brief Get all customers
     * @return Pointer to the head of customer list
     */
    Node<Customer>* getAllCustomers()
    {
        return getAllItems();
    }

    /**
     * @brief Check if a customer exists
     * @param customerId The ID to check
     * @return true if customer exists, false otherwise
     */
    bool customerExists(const std::string& customerId)
    {
        return findCustomerById(customerId) != nullptr;
    }

    /**
     * @brief Get total number of customers
     * @return Number of customers
     */
    int getTotalCustomers()
    {
        return getItemCount();
    }

    /**
     * @brief Delete a customer by ID
     * @param customerId The ID of the customer to delete
     * @return true if the customer was removed, false otherwise
     */
    bool deleteCustomer(const std::string& customerId)
    {
        Node<Customer>* customer = findCustomerById(customerId);
        if (customer == nullptr) return false;
        return dataList.remove(customer->data);
    }

    /**
     * @brief Search customers by keyword in ID, name, or email
     * @param keyword Keyword to search for
     * @return LinkedList containing matching customers
     */
    LinkedList<Customer> searchCustomers(const std::string& keyword)
    {
        LinkedList<Customer> results;
        Node<Customer>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.customerId.find(keyword) != std::string::npos ||
                current->data.fullName.find(keyword) != std::string::npos ||
                current->data.email.find(keyword) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }
};

#endif
