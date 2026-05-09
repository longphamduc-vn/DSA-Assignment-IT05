#ifndef NODE_H
#define NODE_H

// ------------------ Node ------------------
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr) {}
};

#endif
