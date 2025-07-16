#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "json.hpp"
#include <fstream>
using namespace std;
using json = nlohmann ::json;

enum Reserveday
{
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday

};
enum MealType
{
    Breakfast,
    Lunch,
    Dinner,
    Dessert,

};
class Meal
{
    int MealID;
    string MealName;
    float Price;
    MealType mealtype;
    Reserveday reserveday;
    vector<string> SideItems;
    bool IsActive;

public:
    Meal()
    {
        MealID = 0;
        MealName = "";
        Price = 0.0;
        mealtype = Breakfast;
        IsActive = 1;
        reserveday = Saturday;
    }
    Meal(int _mealid, string _mealname, float _price, MealType _mealtype, vector<string> _sideitems, Reserveday _reserveday)
    {
        MealID = _mealid;
        MealName = _mealname;
        Price = _price;
        mealtype = _mealtype;
        reserveday = _reserveday;
        SideItems = _sideitems;
    }

    void setmealid(int _MealID) { MealID = _MealID; }
    void setmealname(string _MealName) { MealName = _MealName; }
    void setprice(float _Price) { Price = _Price; }
    void settype(MealType _mealtype) { mealtype = _mealtype; }
    void setreserveday(Reserveday _Reserveday) { reserveday = _Reserveday; }
    void setsideitems(vector<string> _SideItems) { SideItems = _SideItems; }
    int getmealid() { return MealID; }
    string getmealname() { return MealName; }
    float getprice() { return Price; }
    MealType gettype() { return mealtype; }
    Reserveday getreserveday() { return reserveday; }
    vector<string> getsideitems() { return SideItems; }
    void UpdatPrice(float new_price)
    {
        Price = new_price;
        cout << "new price of " << MealName << " is " << Price << "." << endl;
    }
    void Addsideitem(string item)
    {
        SideItems.push_back(item);
        cout << item << "Added to" << MealName << "as an item ." << endl;
    }
    void printmealinfo()
    {
        cout << "Meal ID:" << MealID << endl;
        cout << "Meal Name :" << MealName << endl;
        cout << "Price :" << Price << endl;
        cout << "Active :" << (IsActive ? "yes" : "No") << endl;
        cout << "Type :";
        switch (mealtype)
        {
        case Breakfast:
            cout << "Breakfast";
            break;
        case Lunch:
            cout << "Lunch";
            break;
        case Dessert:
            cout << "Dessert";
            break;
        case Dinner:
            cout << "Dinner";
            break;
        }
        cout << endl;
        cout << "SideItems :";
        for (size_t i = 0; i < SideItems.size(); i++)
        {
            cout << SideItems[i] << " ";
        }
        cout << endl;
        cout << "\nDay :";
        switch (reserveday)
        {
        case Saturday:
            cout << "Saturday";
            break;
        case Sunday:
            cout << "Sunday";
            break;
        case Monday:
            cout << "Monday";
            break;
        case Tuesday:
            cout << "Tuesday";
            break;
        case Wednesday:
            cout << "Wednesday";
            break;
        case Thursday:
            cout << "Thursday";
            break;
        }
        cout << endl;
    }
    bool isActive() const { return IsActive; }
    void Activate()
    {
        if (IsActive)
            cout << MealName << "Active already." << endl;
        else
        {
            IsActive = true;

            cout << MealName << "Active now." << endl;
        }
    }
    void Deactivate()
    {
        if (!IsActive)
            cout << MealName << "Inactive already." << endl;
        else
        {
            IsActive = false;
            cout << MealName << "Inactive now." << endl;
        }
    }
    json to_json() const
    {
        return {
            {"MealID", MealID},
            {"MealName", MealName},
            {"Price", Price},
            {"mealtype", mealtype},
            {"reserveday", reserveday},
            {"SideItems", SideItems},
            {"IsActive", IsActive}};
    }
    void from_json(const json &j)
    {
        MealID = j.at("MealID").get<int>();
        MealName = j.at("MealName").get<string>();
        Price = j.at("Price").get<float>();
        mealtype = j.at("mealtype").get<MealType>();
        reserveday = j.at("reserveday").get<Reserveday>();
        IsActive = j.at("IsActive").get<bool>();
        SideItems = j.at("SideItems").get<vector<string>>();
    }
};
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
