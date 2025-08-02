#include "includes/admin.hpp"
#include "includes/reservation.hpp"
#include "includes/studentpanel.hpp"
#include "includes/student.hpp"
#include "includes/dininghall.hpp"
#include "includes/meal.hpp"
#include "includes/user.hpp"
#include <fstream>
#include "includes/shoppingcart.hpp"
#include "includes/sessions.hpp"
#include "includes/adminpanel.hpp"
#include <iostream>
using namespace std;

int main()
{
    while (true)
    {
        cout << "\n≡ Welcome to Student Food Reservation System ≡\n";
        cout << "\nSelect Role:\n";
        cout << "1. Student\n";
        cout << "2. Admin\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            StudentPanel sp;
            sp.showMenu();
            break;
        }
        case 2:
        {
            AdminPanel ap;
            ap.showMenu();
            break;
        }
        case 3:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}





