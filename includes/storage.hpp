#include <iostream>
#include <vector>
#include "meal.hpp"
#include "dininghall.hpp"
using namespace std;
class Storage
{
    int MealIDCounter;
    int DiningHallIDCounter;
    vector<Meal> allMeals;
    vector<DiningHall> allDiningHalls;

public:
    Storage()
    {
        MealIDCounter = 0;
        DiningHallIDCounter = 0;
    }
    Storage(const Storage &) = delete;
    Storage operator=(const Storage &) = delete;
    static Storage& instance()
    {
        static Storage storageinstace;
        return storageinstace;
    }
};