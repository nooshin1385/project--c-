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
#include "includes/adminrepo.hpp"
#include "includes/studentdata.hpp"
#include "includes/loginflow.hpp"
#include <iostream>
using namespace std;
vector<Student> allStudents;
#include <limits>
int main()
{
    AdminRepository ad("admin.json");
    ad.checkAdminJson();
    cout << "\n--Welcome to Student Food Reservation System--\n";

    LoginFlow flow;

  

    int choice = 0;
    do
    {
        cout << "\nSelect Role:\n1. Login\n2. Exit\nChoice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1)
        {
            flow.login();
        }
        else if (choice == 2)
        {
            cout << "Exiting...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 2);

    return 0;
}
