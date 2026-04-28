#pragma once
#include "../services/TourService.h"

class Menu {
private:
    TourService tourService;

    void showTourMenu();

public:
    Menu();
    void run();
};