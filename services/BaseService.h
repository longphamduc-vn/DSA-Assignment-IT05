#pragma once
#include "../core/LinkedList.h"
#include <iostream>
#include <string>

template <typename T>
class BaseService {
protected:
    LinkedList<T> list; 

public:
    virtual ~BaseService() {
        list.clear();
    }

    void add(const T& item) {
        list.addTail(item);
    }

    void displayAll() const {
        Node<T>* current = list.getHead();
        if (!current) {
            std::cout << "Danh sach hien dang trong!\n";
            return;
        }
        while (current) {
            std::cout << current->data << "\n";
            current = current->next;
        }
    }

    T* findById(const std::string& id) const {
        Node<T>* current = list.getHead();
        while (current) {
            if (current->data.getId() == id) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    int getSize() const {
        return list.getSize();
    }

    virtual void loadFromFile() = 0;
    virtual void saveToFile() = 0;
};