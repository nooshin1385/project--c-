#pragma once
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
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
        cout << "new price of" << MealName << "is" << Price << "." << endl;
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
        for (int i = 0; i < SideItems.size(); i++)
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
    }
    bool IsActive() const { return IsActive; }
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
};