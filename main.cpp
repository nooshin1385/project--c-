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
#include <iostream>
// #include "bcrypt/BCrypt.hpp"
using namespace std;
vector<Student> allStudents;
int main()
{
    cout << "\n≡ Welcome to Student Food Reservation System ≡\n";

    AdminRepository adminRepo("admins.json");
    if (!adminRepo.exists())
    {
        cout << "\nNo admin found. Please create the first system admin.\n";
        string user, pass;
        cout << "Enter admin username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;
        adminRepo.addAdmin(Admin(user, pass));
        cout << "Admin created successfully.\n";
    }

    int choice;
    do
    {
        cout << "\nSelect Role:\n1. Login\n2. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (adminRepo.validateAdmin(username, password))
            {
                cout << "✔️ Admin login successful.\n";
                AdminPanel().showMenu();
            }
            else
            {
                Student *student = StudentsData::findStudentByIdAndPassword(username, password);
                if (student)
                {
                    cout << "Student login successful.\n";
                    StudentPanel panel;
                    panel.setStudent(student);
                    panel.showMenu();
                }
                else
                {
                    cout << "Invalid credentials.\n";
                }
            }
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
