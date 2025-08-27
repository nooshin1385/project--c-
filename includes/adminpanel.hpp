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
    void EditMeal(vector<Meal> &meals)
    {
        int id;
        cout << "Enter Meal ID to edit: ";
        cin >> id;

        auto it = find_if(meals.begin(), meals.end(),
                          [id](const Meal &m)
                          { return m.getmealid() == id; });

        if (it != meals.end())
        {
            int choice;
            do
            {
                cout << "\n--- Editing Meal: " << it->getmealname() << " ---\n";
                cout << "1. Change name\n";
                cout << "2. Change price\n";
                cout << "3. Show side items\n";
                cout << "4. Add side item\n";
                cout << "5. Remove side item\n";
                cout << "6. Finish editing\n";
                cout << "Choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    string newName;
                    cout << "New name: ";
                    cin >> newName;
                    it->setmealname(newName);
                    break;
                }
                case 2:
                {
                    float newPrice;
                    cout << "New price: ";
                    cin >> newPrice;
                    it->setprice(newPrice);
                    break;
                }
                case 3:
                {
                    cout << "Side items:\n";
                    for (auto &s : it->getsideitems())
                        cout << " - " << s << "\n";
                    break;
                }
                case 4:
                {
                    string side;
                    cout << "Enter new side item: ";
                    cin >> side;
                    it->Addsideitem(side);
                    break;
                }
                case 5:
                {
                    string side;
                    cout << "Enter side item to remove: ";
                    cin >> side;
                    it->Removesideitem(side);
                    break;
                }
                case 6:
                    cout << "Editing finished.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
                }
            } while (choice != 6);
        }
        else
        {
            cout << "Meal not found.\n";
        }
    }

    void DeleteMeal()
    {
        int id;
        cout << "Enter Meal ID to delete: ";
        cin >> id;

        auto it = remove_if(meals.begin(), meals.end(),
                            [id](const Meal &m)
                            { return m.getmealid() == id; });

        if (it != meals.end())
        {
            meals.erase(it, meals.end());
            cout << "Meal deleted.\n";
        }
        else
        {
            cout << "Meal not found.\n";
        }
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
            system("notepad meals.json");
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
        loadMealsFromFile();
        loadDininghallsFromFile();
        int choice;
        do
        {
            cout << "\n----- ADMIN PANEL -----\n";
            cout << "1. Login\n";
            cout << "2. Add meal\n";
            cout << "3. Edit meal\n";
            cout << "4. Delete meal\n";
            cout << "5. View meals\n";
            cout << "6. Logout\n";
            cout << "7. Save meals to file\n";
            cout << "8. Load meals from file\n";
            cout << "9. Add dining hall\n";
            cout << "10. View dining hall\n";
            cout << "11. Exit\n";
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
                EditMeal(meals);
                break;
            case 4:
                DeleteMeal();
                break;
            case 5:
                listMeals();
                break;
            case 6:
                logout();
                break;
            case 7:
                saveMealsToFile();
                break;
            case 8:
                loadMealsFromFile();
                break;
            case 9:
                Adddininghall();
                break;
            case 10:
                Listdininghalls();
                break;
            case 11:
                saveMealsToFile();
                saveDininghallsToFile();
                cout << "exiting admin panel...\n";
                break;
            default:
                cout << "invalid choice.\n";
            }
        } while (choice != 11);
    }
};