#include <iostream>
#include <cassert>
#include <string>
#include "../core/LinkedList.h"
#include "../models/Employee.h"

using namespace std;

/**
 * @brief Test suite for LinkedList with Employee Model
 */

void testInsertEmployeeHead()
{
    cout << "\n[TEST] Insert Employee at HEAD" << endl;
    LinkedList<Employee> list;
    
    Employee emp1, emp2, emp3;
    
    emp1.employeeId = "E001";
    emp1.fullName = "John Doe";
    emp1.position = "Tour Guide";
    emp1.phoneNumber = "0123456789";
    emp1.email = "john@example.com";
    
    emp2.employeeId = "E002";
    emp2.fullName = "Jane Smith";
    emp2.position = "Receptionist";
    emp2.phoneNumber = "0987654321";
    emp2.email = "jane@example.com";
    
    emp3.employeeId = "E003";
    emp3.fullName = "Bob Johnson";
    emp3.position = "Driver";
    emp3.phoneNumber = "0555555555";
    emp3.email = "bob@example.com";
    
    list.insert(emp1, INSERT_HEAD);
    list.insert(emp2, INSERT_HEAD);
    list.insert(emp3, INSERT_HEAD);
    
    cout << "List size: " << list.getSize() << endl;
    assert(list.getSize() == 3);
    
    // Verify order (last inserted should be first: E003, E002, E001)
    Employee first = list.getAt(0);
    assert(first.employeeId == "E003");
    
    Employee second = list.getAt(1);
    assert(second.employeeId == "E002");
    
    Employee third = list.getAt(2);
    assert(third.employeeId == "E001");
    
    cout << "✓ PASSED\n";
}

void testInsertEmployeeTail()
{
    cout << "[TEST] Insert Employee at TAIL" << endl;
    LinkedList<Employee> list;
    
    Employee emp1, emp2, emp3;
    
    emp1.employeeId = "E001";
    emp1.fullName = "Alice";
    emp1.position = "Manager";
    emp1.phoneNumber = "1111111111";
    emp1.email = "alice@example.com";
    
    emp2.employeeId = "E002";
    emp2.fullName = "Bob";
    emp2.position = "Developer";
    emp2.phoneNumber = "2222222222";
    emp2.email = "bob@example.com";
    
    emp3.employeeId = "E003";
    emp3.fullName = "Charlie";
    emp3.position = "Tester";
    emp3.phoneNumber = "3333333333";
    emp3.email = "charlie@example.com";
    
    list.insert(emp1, INSERT_TAIL);
    list.insert(emp2, INSERT_TAIL);
    list.insert(emp3, INSERT_TAIL);
    
    cout << "Employees added (order should be E001, E002, E003):" << endl;
    cout << "  [1] " << list.getAt(0).fullName << " (" << list.getAt(0).employeeId << ")" << endl;
    cout << "  [2] " << list.getAt(1).fullName << " (" << list.getAt(1).employeeId << ")" << endl;
    cout << "  [3] " << list.getAt(2).fullName << " (" << list.getAt(2).employeeId << ")" << endl;
    
    assert(list.getSize() == 3);
    assert(list.getAt(0).employeeId == "E001");
    assert(list.getAt(1).employeeId == "E002");
    assert(list.getAt(2).employeeId == "E003");
    cout << "✓ PASSED\n";
}

void testSearchEmployee()
{
    cout << "[TEST] Search for Employee" << endl;
    LinkedList<Employee> list;
    
    Employee emp1, emp2, emp3;
    
    emp1.employeeId = "E001";
    emp1.fullName = "John";
    emp1.position = "Tour Guide";
    emp1.phoneNumber = "0111111111";
    emp1.email = "john@example.com";
    
    emp2.employeeId = "E002";
    emp2.fullName = "Jane";
    emp2.position = "Manager";
    emp2.phoneNumber = "0222222222";
    emp2.email = "jane@example.com";
    
    emp3.employeeId = "E003";
    emp3.fullName = "Bob";
    emp3.position = "Staff";
    emp3.phoneNumber = "0333333333";
    emp3.email = "bob@example.com";
    
    list.insert(emp1, INSERT_TAIL);
    list.insert(emp2, INSERT_TAIL);
    list.insert(emp3, INSERT_TAIL);
    
    // Search by comparing fullName
    Node<Employee>* found = list.search(emp2);
    assert(found != nullptr);
    assert(found->data.fullName == "Jane");
    
    cout << "Found employee: " << found->data.fullName 
         << " (" << found->data.employeeId << ")" << endl;
    cout << "✓ PASSED\n";
}

void testExistsEmployee()
{
    cout << "[TEST] Check if Employee exists" << endl;
    LinkedList<Employee> list;
    
    Employee emp1;
    emp1.employeeId = "E001";
    emp1.fullName = "Michael";
    emp1.position = "Coordinator";
    emp1.phoneNumber = "0444444444";
    emp1.email = "michael@example.com";
    
    Employee emp2;
    emp2.employeeId = "E002";
    emp2.fullName = "Sarah";
    emp2.position = "Designer";
    emp2.phoneNumber = "0555555555";
    emp2.email = "sarah@example.com";
    
    Employee notInList;
    notInList.employeeId = "E999";
    notInList.fullName = "Ghost";
    notInList.position = "Unknown";
    notInList.phoneNumber = "0000000000";
    notInList.email = "ghost@example.com";
    
    list.insert(emp1, INSERT_TAIL);
    list.insert(emp2, INSERT_TAIL);
    
    assert(list.exists(emp1) == true);
    assert(list.exists(emp2) == true);
    assert(list.exists(notInList) == false);
    
    cout << "Employee existence checks passed" << endl;
    cout << "✓ PASSED\n";
}

void testRemoveEmployee()
{
    cout << "[TEST] Remove Employee from list" << endl;
    LinkedList<Employee> list;
    
    Employee emp1, emp2, emp3;
    
    emp1.employeeId = "E001";
    emp1.fullName = "Employee1";
    emp1.position = "Position1";
    emp1.phoneNumber = "1111111111";
    emp1.email = "emp1@example.com";
    
    emp2.employeeId = "E002";
    emp2.fullName = "Employee2";
    emp2.position = "Position2";
    emp2.phoneNumber = "2222222222";
    emp2.email = "emp2@example.com";
    
    emp3.employeeId = "E003";
    emp3.fullName = "Employee3";
    emp3.position = "Position3";
    emp3.phoneNumber = "3333333333";
    emp3.email = "emp3@example.com";
    
    list.insert(emp1, INSERT_TAIL);
    list.insert(emp2, INSERT_TAIL);
    list.insert(emp3, INSERT_TAIL);
    
    cout << "Initial size: " << list.getSize() << endl;
    assert(list.getSize() == 3);
    
    // Remove middle employee
    bool removed = list.remove(emp2);
    cout << "Removed emp2: " << (removed ? "true" : "false") << endl;
    assert(removed == true);
    assert(list.getSize() == 2);
    
    cout << "After removal size: " << list.getSize() << endl;
    cout << "✓ PASSED\n";
}

void testGetAtEmployee()
{
    cout << "[TEST] Get Employee at specific index" << endl;
    LinkedList<Employee> list;
    
    Employee emp1, emp2, emp3;
    
    emp1.employeeId = "E001";
    emp1.fullName = "First";
    emp1.position = "Position1";
    emp1.phoneNumber = "1111111111";
    emp1.email = "first@example.com";
    
    emp2.employeeId = "E002";
    emp2.fullName = "Second";
    emp2.position = "Position2";
    emp2.phoneNumber = "2222222222";
    emp2.email = "second@example.com";
    
    emp3.employeeId = "E003";
    emp3.fullName = "Third";
    emp3.position = "Position3";
    emp3.phoneNumber = "3333333333";
    emp3.email = "third@example.com";
    
    list.insert(emp1, INSERT_TAIL);
    list.insert(emp2, INSERT_TAIL);
    list.insert(emp3, INSERT_TAIL);
    
    Employee at0 = list.getAt(0);
    Employee at1 = list.getAt(1);
    Employee at2 = list.getAt(2);
    
    cout << "Employee at index 0: " << at0.fullName << " (" << at0.employeeId << ")" << endl;
    cout << "Employee at index 1: " << at1.fullName << " (" << at1.employeeId << ")" << endl;
    cout << "Employee at index 2: " << at2.fullName << " (" << at2.employeeId << ")" << endl;
    
    assert(at0.employeeId == "E001");
    assert(at1.employeeId == "E002");
    assert(at2.employeeId == "E003");
    
    // Test out of bounds
    try
    {
        list.getAt(10);
        assert(false);  // Should throw exception
    }
    catch (const std::out_of_range& e)
    {
        cout << "Out of range exception caught correctly" << endl;
    }
    cout << "✓ PASSED\n";
}

void testClearEmployees()
{
    cout << "[TEST] Clear Employee list" << endl;
    LinkedList<Employee> list;
    
    Employee emp;
    emp.employeeId = "E001";
    emp.fullName = "Test Employee";
    emp.position = "Tester";
    emp.phoneNumber = "0111111111";
    emp.email = "test@example.com";
    
    list.insert(emp, INSERT_TAIL);
    list.insert(emp, INSERT_TAIL);
    list.insert(emp, INSERT_TAIL);
    
    cout << "Size before clear: " << list.getSize() << endl;
    assert(list.getSize() == 3);
    
    list.clear();
    cout << "Size after clear: " << list.getSize() << endl;
    assert(list.getSize() == 0);
    cout << "✓ PASSED\n";
}

void testDisplayEmployees()
{
    cout << "[TEST] Display Employee Information" << endl;
    LinkedList<Employee> list;
    
    Employee emp1, emp2;
    
    emp1.employeeId = "E001";
    emp1.fullName = "Alex";
    emp1.position = "Manager";
    emp1.phoneNumber = "0123456789";
    emp1.email = "alex@example.com";
    
    emp2.employeeId = "E002";
    emp2.fullName = "Jordan";
    emp2.position = "Developer";
    emp2.phoneNumber = "0987654321";
    emp2.email = "jordan@example.com";
    
    list.insert(emp1, INSERT_TAIL);
    list.insert(emp2, INSERT_TAIL);
    
    cout << "\nEmployee List Details:" << endl;
    for (size_t i = 0; i < list.getSize(); i++)
    {
        Employee e = list.getAt(i);
        cout << "[" << i + 1 << "]" << endl;
        cout << "  ID:       " << e.employeeId << endl;
        cout << "  Name:     " << e.fullName << endl;
        cout << "  Position: " << e.position << endl;
        cout << "  Phone:    " << e.phoneNumber << endl;
        cout << "  Email:    " << e.email << endl;
    }
    
    cout << "\n✓ PASSED\n";
}

int main()
{
    cout << "====== LinkedList<Employee> Test Suite ======\n";
    
    try
    {
        testInsertEmployeeHead();
        testInsertEmployeeTail();
        testSearchEmployee();
        testExistsEmployee();
        testRemoveEmployee();
        testGetAtEmployee();
        testClearEmployees();
        testDisplayEmployees();
        
        cout << "====== ALL TESTS PASSED ✓ ======\n";
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "\n✗ TEST FAILED: " << e.what() << endl;
        return 1;
    }
}
