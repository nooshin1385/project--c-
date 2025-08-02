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
    void Adddininghall()
    {
        int Id, Capacity;
        string Name, Address;
        cout << "Enter dininghall Id :";
        cin >> Id;
        cout << "Enter Name :";
        cin.ignore();
        getline(cin, Name);
        cout << "Enter address :";
        getline(cin, Address);
        cout << "Enter capacity:";
        cin >> Capacity;
        DiningHall hall(Id, Name, Address, Capacity);
        halls.push_back(hall);
        cout << "Dininghall added successfully.\n";
    }
    void Listdininghalls()
    {
        if (halls.empty())
        {
            cout << "There is not any Dininghall \n";
        }
        else
        {
            for (const DiningHall &h : halls)
            {
                h.printdininghallinfo();
            }
        }
    }
    void saveDininghallsToFile(const string &filename = "dininghalls.json")
    {
        json j;
        for (const DiningHall &d : halls)
        {
            j.push_back(d.to_json());
        }
        ofstream out(filename);
        if (out.is_open())
        {
            out << j.dump(4);
            out.close();
            cout << "Dining halls saved to file\n";
        }
        else
        {
            cerr << "Failed to open file for writing.\n";
        }
    }
    void loadDininghallsFromFile(const string &filename = "dininghalls.json")
    {
        ifstream in(filename);
        if (!in.is_open())
        {
            cerr << "Could not open dininghalls file.\n";
            return;
        }

        json j;
        in >> j;
        in.close();

        halls.clear();
        for (const auto &item : j)
        {
            DiningHall d;
            d.from_json(item);
            halls.push_back(d);
        }

        cout << "Dining halls loaded from file\n";
    }

public:
    void saveMealsToFile()
    {
        json j;
        for (const Meal &m : meals)
        {
            j.push_back(m.to_json());
        }

        ofstream out("meals.json");
        if (out.is_open())
        {
            out << j.dump(4);
            out.close();
            cout << "Meals saved successfully.\n";
        }
        else
        {
            cout << "Failed to save meals to file.\n";
        }
    }
    void loadMealsFromFile()
    {
        ifstream in("meals.json");
        if (!in.is_open())
        {
            cout << "No previous meals data found.\n";
            return;
        }

        json j;
        in >> j;
        meals.clear();

        for (const auto &item : j)
        {
            Meal m;
            m.from_json(item);
            meals.push_back(m);
        }

        cout << "Meals loaded successfully.\n";
    }
    void showMenu()
    {
        loadDininghallsFromFile();
        int choice;
        do
        {
            cout << "\n----- ADMIN PANEL -----\n";
            cout << "1. Login\n";
            cout << "2. Add meal\n";
            cout << "3. View meals\n";
            cout << "4. Logout\n";
            cout << "5. Save meals to file\n";
            cout << "6. Load meals from file\n";
            cout << "5. Add dining hall\n";
            cout << "6. View dining hall\n";
            cout << "7. Exit\n";
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
                saveMealsToFile();
                break;
            case 6:
                loadMealsFromFile();
                break;
            case 7:
                Adddininghall();
                break;
            case 8:
                Listdininghalls();
                break;
            case 9:
                saveDininghallsToFile();
                cout << "exiting admin panel...\n";
                break;
            default:
                cout << "invalid choice.\n";
            }
        } while (choice != 9);
    }
};