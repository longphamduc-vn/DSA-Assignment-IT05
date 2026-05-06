// ==========================================
// File: services/GenericService.h
// Description: Lớp cơ sở dùng chung cho mọi Service (Template Method Pattern)
// ==========================================
#ifndef GENERIC_SERVICE_H
#define GENERIC_SERVICE_H

#include "../core/LinkedList.h"
#include <string>

template <typename T>
class GenericService {
protected:
    LinkedList<T> repository;

public:
    virtual ~GenericService() {}
    
    // Create
    virtual void add(const T& item) {
        repository.addLast(item);
    }
    
    // Abstract methods cho Update và Delete (Do mỗi model có ID khác nhau)
    virtual bool update(const std::string& id, const T& updatedItem) = 0;
    virtual bool remove(const std::string& id) = 0;
    
    LinkedList<T>& getRepository() {
        return repository;
    }
};

#endif // GENERIC_SERVICE_H