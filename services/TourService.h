// ==========================================
// File: services/TourService.h
// Description: Nghiệp vụ quản lý Tour Du lịch
// ==========================================
#ifndef TOUR_SERVICE_H
#define TOUR_SERVICE_H

#include "GenericService.h"
#include "../models/Tour.h"

class TourService : public GenericService<Tour> {
public:
    // --- 2.1. YÊU CẦU 2: CRUD ---
    bool update(const std::string& id, const Tour& updatedData) override {
        Tour* tour = repository.findIf([id](const Tour& t) { return t.tourId == id; });
        if (tour) {
            *tour = updatedData;
            tour->tourId = id; // Không cho phép đổi ID
            return true;
        }
        return false;
    }

    bool remove(const std::string& id) override {
        // Lưu ý: Logic kiểm tra "chưa có Booking nào" sẽ được xử lý ở Menu/Controller
        // bằng cách gọi BookingService kiểm tra trước khi gọi hàm này.
        return repository.removeIf([id](const Tour& t) { return t.tourId == id; });
    }

    Tour* findById(const std::string& id) {
        return repository.findIf([id](const Tour& t) { return t.tourId == id; });
    }

    // --- 3. YÊU CẦU 3: TÌM KIẾM ---
    LinkedList<Tour> searchByPriceRange(double minPrice, double maxPrice) {
        return repository.filter([minPrice, maxPrice](const Tour& t) {
            return t.price >= minPrice && t.price <= maxPrice;
        });
    }

    LinkedList<Tour> searchByDepartureDate(const std::string& date) {
        return repository.filter([date](const Tour& t) { return t.departureDate == date; });
    }

    LinkedList<Tour> searchByDestination(const std::string& dest) {
        return repository.filter([dest](const Tour& t) { 
            return t.destination.find(dest) != std::string::npos; 
        });
    }

    // --- 4. YÊU CẦU 4: SẮP XẾP ---
    void sortByPrice(bool ascending = true) {
        repository.sort([ascending](const Tour& a, const Tour& b) {
            return ascending ? (a.price < b.price) : (a.price > b.price);
        });
    }

    void sortByDepartureDate() {
        // Chuỗi YYYY-MM-DD có thể so sánh trực tiếp bằng toán tử <
        repository.sort([](const Tour& a, const Tour& b) {
            return a.departureDate < b.departureDate;
        });
    }

    // --- 5 & 6 & 7. YÊU CẦU THỐNG KÊ, MIN/MAX ---
    Tour* getMostExpensiveTour() {
        Tour* maxTour = nullptr;
        repository.forEach([&maxTour](Tour& t) {
            if (!maxTour || t.price > maxTour->price) maxTour = &t;
        });
        return maxTour;
    }

    int countTotalAvailableSeats() {
        int total = 0;
        repository.forEach([&total](const Tour& t) { total += t.availableSeats; });
        return total;
    }

    double getAveragePrice() {
        if (repository.isEmpty()) return 0;
        double sum = 0;
        repository.forEach([&sum](const Tour& t) { sum += t.price; });
        return sum / repository.getSize();
    }

    LinkedList<Tour> getSoldOutTours() {
        return repository.filter([](const Tour& t) { return t.availableSeats == 0; });
    }
};

#endif // TOUR_SERVICE_H