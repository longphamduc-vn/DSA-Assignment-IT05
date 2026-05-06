// ==========================================
// File: core/LinkedList.h
// Author: Phạm Đức Long
// Description: Advanced Generic Linked List Implementation 
//              Includes O(N log N) Merge Sort and Lambda-based Iterators
// ==========================================
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <functional>

// ==========================================
// 1. Định nghĩa Cấu trúc Node
// ==========================================
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T val) : data(val), next(nullptr) {}
};

// ==========================================
// 2. Định nghĩa Lớp LinkedList
// ==========================================
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    // Các hàm Helper private hỗ trợ thuật toán Merge Sort trên Linked List
    Node<T>* getMiddle(Node<T>* h) {
        if (!h || !h->next) return h;
        Node<T>* slow = h;
        Node<T>* fast = h->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node<T>* merge(Node<T>* left, Node<T>* right, std::function<bool(const T&, const T&)> compare) {
        if (!left) return right;
        if (!right) return left;

        Node<T>* result = nullptr;
        // Gọi hàm so sánh được truyền vào để quyết định thứ tự
        if (compare(left->data, right->data)) {
            result = left;
            result->next = merge(left->next, right, compare);
        } else {
            result = right;
            result->next = merge(left, right->next, compare);
        }
        return result;
    }

    Node<T>* mergeSort(Node<T>* h, std::function<bool(const T&, const T&)> compare) {
        if (!h || !h->next) return h;

        Node<T>* middle = getMiddle(h);
        Node<T>* nextToMiddle = middle->next;
        middle->next = nullptr;

        Node<T>* left = mergeSort(h, compare);
        Node<T>* right = mergeSort(nextToMiddle, compare);

        return merge(left, right, compare);
    }


    void updateTail() {
        if (!head) {
            tail = nullptr;
            return;
        }
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        tail = current;
    }

public:
    // ==========================================
    // Constructor & Destructor
    // ==========================================
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    // ==========================================
    // Thao tác Thêm (Insert)
    // ==========================================
    void addLast(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void addFirst(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    // ==========================================
    // Thao tác Xóa (Remove)
    // ==========================================
    // Xóa node đầu tiên thỏa mãn điều kiện truyền vào qua lambda
    bool removeIf(std::function<bool(const T&)> condition) {
        if (!head) return false;

        // Nếu node cần xóa là node đầu
        if (condition(head->data)) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            if (!head) tail = nullptr;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr) {
            if (condition(current->next->data)) {
                Node<T>* temp = current->next;
                current->next = current->next->next;
                if (temp == tail) {
                    tail = current;
                }
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    // ==========================================
    // Thao tác Tìm kiếm (Search & Filter)
    // ==========================================
    // Tìm phần tử đầu tiên thỏa mãn điều kiện, trả về con trỏ tới data (nullptr nếu không thấy)
    T* findIf(std::function<bool(const T&)> condition) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (condition(current->data)) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    // Lọc ra một danh sách mới chứa tất cả các phần tử thỏa mãn điều kiện
    LinkedList<T> filter(std::function<bool(const T&)> condition) const {
        LinkedList<T> resultList;
        Node<T>* current = head;
        while (current != nullptr) {
            if (condition(current->data)) {
                resultList.addLast(current->data);
            }
            current = current->next;
        }
        return resultList;
    }

    // ==========================================
    // Thao tác Sắp xếp (Sort) - Yêu cầu 4
    // ==========================================
    // Sắp xếp danh sách sử dụng Merge Sort O(N log N) dựa trên lambda so sánh
    void sort(std::function<bool(const T&, const T&)> compare) {
        if (!head || !head->next) return;
        head = mergeSort(head, compare);
        updateTail();
    }

    // ==========================================
    // Thao tác Lặp (Iteration)
    // ==========================================
    // Duyệt qua toàn bộ danh sách và thực thi một hàm (dùng để in hoặc tính tổng)
    void forEach(std::function<void(T&)> action) {
        Node<T>* current = head;
        while (current != nullptr) {
            action(current->data);
            current = current->next;
        }
    }

    void forEach(std::function<void(const T&)> action) const {
        Node<T>* current = head;
        while (current != nullptr) {
            action(current->data);
            current = current->next;
        }
    }

    // ==========================================
    // Getter
    // ==========================================
    Node<T>* getHead() const { return head; }
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
};

#endif