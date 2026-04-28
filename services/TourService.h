#pragma once
#include "BaseService.h"
#include "../models/Tour.h"
#include <string>

class TourService : public BaseService<Tour> {
private:
    std::string filePath;

public:
    TourService(std::string path);
    ~TourService();

    void loadFromFile() override;
    void saveToFile() override;

    void updatePrice(std::string id, double newPrice);
    void sortByPriceAsc();
    void showMaxPriceTour();
    void showStats();
};