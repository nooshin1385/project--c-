#pragma once
#include "sessions.hpp"
#include <iostream>
#include "meal.hpp"
#include "dininghall.hpp"
#include "admin.hpp"

using namespace std;

class AdminPanel
{
private:
    vector<Meal> meals;
    vector<DiningHall> halls;

    void login()
    {
        string username, password;
        cout << "Admin Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        AdminSession::SessionManager::getinstance()->Login_Session(username, password);
    }

    void logout()
    {
        AdminSession::SessionManager::getinstance()->logout();
    }

    void addMeal()
    {
        int id;
        string name;
        float price;
        int type, day;
        int n;
        vector<string> sides;

        cout << "Meal ID: ";
        cin >> id;
        cout << "Name: ";
        cin >> name;
        cout << "Price: ";
        cin >> price;
        cout << "Type (1.Breakfast 2.Lunch 3.Dinner 4.Dessert): ";
        cin >> type;
        cout << "Day (1.Saturday ... 6.Thursday): ";
        cin >> day;
        cout << "Number of side items: ";
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            string item;
            cout << "item " << i + 1 << ": ";
            cin >> item;
            sides.push_back(item);
        }

        Meal m(id, name, price, (MealType)type, sides, (Reserveday)day);
        meals.push_back(m);
        cout << "meal added.\n";
    }

    void listMeals()
    {
        if (meals.empty())
        {
            cout << "no meal added yet.\n";
        }
        else
        {
            for (Meal &m : meals)
            {
                m.printmealinfo();
                cout << "-------------------\n";
            }
        }
    }

public:
    void showMenu()
    {
        int choice;
        do
        {
            cout << "\n----- ADMIN PANEL -----\n";
            cout << "1. Login\n";
            cout << "2. Add meal\n";
            cout << "3. View meals\n";
            cout << "4. Logout\n";
            cout << "5. Exit\n";
            cout << "choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                login();
                break;
            case 2:
                addMeal();
                break;
            case 3:
                listMeals();
                break;
            case 4:
                logout();
                break;
            case 5:
                cout << "exiting admin panel...\n";
                break;
            default:
                cout << "invalid choice.\n";
            }
        } while (choice != 5);
    }
};