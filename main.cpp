#include "includes/admin.hpp"
#include "includes/reservation.hpp"
//#include "includes/studentpanel.hpp"
#include "includes/student.hpp"
#include "includes/dininghall.hpp"
#include "includes/meal.hpp"
#include "includes/user.hpp"
#include <fstream>

int main()
{
    // 1. ساخت یک شیء Meal
    Meal myMeal(1, "Pizza", 75000.0, Lunch, {"Salad", "Drink"}, Tuesday);

    // 2. تبدیل به json
    json j = myMeal.to_json();

    // 3. ذخیره در فایل
    ofstream outFile("meal.json");
    if (outFile.is_open())
    {
        outFile << j.dump(4); // 4 برای زیبایی خروجی
        outFile.close();
        cout << "Meal saved to meal.json ✅" << endl;
    }
    else
    {
        cerr << "Failed to open meal.json ❌" << endl;
    }

    // 4. خواندن مجدد از فایل
    ifstream inFile("meal.json");
    if (inFile.is_open())
    {
        json loadedJson;
        inFile >> loadedJson;
        inFile.close();

        Meal loadedMeal;
        loadedMeal.from_json(loadedJson);

        cout << "\nLoaded meal info from JSON file:" << endl;
        loadedMeal.printmealinfo();
    }
    else
    {
        cerr << "Failed to read meal.json ❌" << endl;
    }

    return 0;
}
