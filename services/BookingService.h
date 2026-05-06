// ==========================================
// File: services/BookingService.h
// Description: Nghiệp vụ quản lý Đơn đặt Tour, xử lý tương tác chéo với TourService
// ==========================================
#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include "GenericService.h"
#include "TourService.h"
#include "CustomerService.h"
#include "EmployeeService.h"
#include "../models/Booking.h"

class BookingService : public GenericService<Booking>
{
public:
    // --- 2.3. YÊU CẦU 2: TẠO VÀ XỬ LÝ BOOKING ---
    // Tạo Booking mới: Tự động trừ AvailableSeats
    bool createBooking(Booking &b, TourService &ts, CustomerService &cs, EmployeeService &es)
    {
        Tour *tour = ts.findById(b.tourId);
        if (!tour || tour->availableSeats < b.passengerCount)
            return false;

        tour->availableSeats -= b.passengerCount;
        b.totalAmount = b.passengerCount * tour->price;
        b.status = "Confirmed";

        // Cập nhật thống kê
        cs.addTotalSpent(b.customerId, b.totalAmount);
        es.addSale(b.employeeId, b.totalAmount);

        repository.addLast(b);
        return true;
    }

    bool update([[maybe_unused]] const std::string &id, [[maybe_unused]] const Booking &updatedData) override
    {
        
        return false;
    }

    bool remove(const std::string &id) override
    {
        return repository.removeIf([id](const Booking &b)
                                   { return b.bookingId == id; });
    }

    // Đổi trạng thái Booking và hoàn/trừ chỗ tương ứng
    bool changeBookingStatus(const std::string &id, const std::string &newStatus, TourService &ts)
    {
        Booking *b = repository.findIf([id](const Booking &book)
                                       { return book.bookingId == id; });
        if (!b)
            return false;

        if (b->status == "Confirmed" && newStatus == "Cancelled")
        {
            Tour *t = ts.findById(b->tourId);
            if (t)
                t->availableSeats += b->passengerCount; // Hoàn chỗ
        }
        b->status = newStatus;
        return true;
    }

    // --- YÊU CẦU 3 & 4: TÌM KIẾM, SẮP XẾP ---
    LinkedList<Booking> getBookingsByCustomer(const std::string &custId)
    {
        return repository.filter([custId](const Booking &b)
                                 { return b.customerId == custId; });
    }

    void sortByTotalAmount()
    {
        repository.sort([](const Booking &a, const Booking &b)
                        {
                            return a.totalAmount > b.totalAmount; // Giảm dần
                        });
    }

    void sortByBookingDate()
    {
        repository.sort([](const Booking &a, const Booking &b)
                        {
                            return a.bookingDate > b.bookingDate; // Mới nhất lên đầu
                        });
    }

    // --- YÊU CẦU 6 & 7: THỐNG KÊ TỔNG HỢP ---
    double calculateTotalRevenue()
    {
        double total = 0;
        repository.forEach([&total](const Booking &b)
                           {
            if (b.status == "Confirmed") total += b.totalAmount; });
        return total;
    }

    double calculateCancellationRate()
    {
        if (repository.isEmpty())
            return 0;
        int cancelled = 0;
        repository.forEach([&cancelled](const Booking &b)
                           {
            if (b.status == "Cancelled") cancelled++; });
        return (double)cancelled / repository.getSize() * 100.0;
    }
};

#endif // BOOKING_SERVICE_H