#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include <string>
#include <iostream>
#include <map>
#include "GenericService.h"
#include "../models/Employee.h"
#include "../core/LinkedList.h"

/**
 * @brief Service class for managing Employee operations
 */
class EmployeeService : public GenericService<Employee>
{
public:
    /**
     * @brief Constructor
     */
    EmployeeService() {}

    /**
     * @brief Add a new employee
     * @param employee The employee object to add
     */
    void addEmployee(const Employee& employee)
    {
        addItem(employee);
    }

    /**
     * @brief Search for an employee by ID
     * @param employeeId The ID to search for
     * @return Pointer to the found employee node, nullptr if not found
     */
    Node<Employee>* findEmployeeById(const std::string& employeeId)
    {
        Node<Employee>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.employeeId == employeeId)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /**
     * @brief Search for employees by name (partial match)
     * @param name The name to search for
     * @return LinkedList containing matching employees
     */
    LinkedList<Employee> findEmployeeByName(const std::string& name)
    {
        LinkedList<Employee> results;
        Node<Employee>* current = dataList.getHead();
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
     * @brief Search for employees by position
     * @param position The position to search for
     * @return LinkedList containing employees with the specified position
     */
    LinkedList<Employee> findEmployeeByPosition(const std::string& position)
    {
        LinkedList<Employee> results;
        Node<Employee>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.position == position)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Update an existing employee
     * @param employeeId The ID of employee to update
     * @param updatedEmployee The updated employee data
     * @return true if update was successful, false otherwise
     */
    bool updateEmployee(const std::string& employeeId, const Employee& updatedEmployee)
    {
        Node<Employee>* employee = findEmployeeById(employeeId);
        if (employee != nullptr)
        {
            employee->data = updatedEmployee;
            return true;
        }
        return false;
    }


    /**
     * @brief Get all employees
     * @return Pointer to the head of employee list
     */
    Node<Employee>* getAllEmployees()
    {
        return getAllItems();
    }

    /**
     * @brief Check if an employee exists
     * @param employeeId The ID to check
     * @return true if employee exists, false otherwise
     */
    bool employeeExists(const std::string& employeeId)
    {
        return findEmployeeById(employeeId) != nullptr;
    }

    /**
     * @brief Get total number of employees
     * @return Number of employees
     */
    int getTotalEmployees()
    {
        return getItemCount();
    }

    /**
     * @brief Delete an employee by ID
     * @param employeeId The ID of the employee to delete
     * @return true if the employee was removed, false otherwise
     */
    bool deleteEmployee(const std::string& employeeId)
    {
        Node<Employee>* employee = findEmployeeById(employeeId);
        if (employee == nullptr) return false;
        return dataList.remove(employee->data);
    }

    /**
     * @brief Search employees by keyword in ID, name, or position
     * @param keyword Keyword to search for
     * @return LinkedList containing matching employees
     */
    LinkedList<Employee> searchEmployees(const std::string& keyword)
    {
        LinkedList<Employee> results;
        Node<Employee>* current = dataList.getHead();
        while (current != nullptr)
        {
            if (current->data.employeeId.find(keyword) != std::string::npos ||
                current->data.fullName.find(keyword) != std::string::npos ||
                current->data.position.find(keyword) != std::string::npos)
            {
                results.insert(current->data, INSERT_TAIL);
            }
            current = current->next;
        }
        return results;
    }

    /**
     * @brief Thống kê số lượng nhân viên theo chức vụ
     */
    std::map<std::string, int> countEmployeesByPosition() const {
        std::map<std::string, int> posCount;
        Node<Employee>* current = dataList.getHead();
        while (current != nullptr) {
            posCount[current->data.position]++;
            current = current->next;
        }
        return posCount;
    }
};

#endif
