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
#include <iostream>
// #include "bcrypt/BCrypt.hpp"
using namespace std;
vector<Student> allStudents;

int main()
{
    cout << "\n Welcome to Student Food Reservation System \n";
    AdminRepository repo("admins.json");
    if (!repo.exists())
    {
        cout << "⚠️ No admin found. Please create the first system admin.\n";
        string user, pass;
        cout << "Enter admin username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;
        repo.addAdmin(Admin(user, pass));
        cout << "✅ Admin created successfully.\n";
    }

    int choice;
    do
    {
        cout << "\nSelect Role:\n"
             << "1. Student\n"
             << "2. Admin\n"
             << "3. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            StudentSession::SessionManager::getinstance()->load_Session();
            StudentPanel().showMenu();
            break;

        case 2:
            AdminPanel().showMenu();
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
