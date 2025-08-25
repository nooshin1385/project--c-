#include "loginflow.hpp"
#include "adminrepo.hpp"
#include "studentdata.hpp"
#include "studentpanel.hpp"
#include "adminpanel.hpp"
#include <iostream>
using namespace std;

void LoginFlow::login()
{
    AdminRepository adminRepo("admins.json");

    string username;
    cout << "Username: ";
    cin >> username;

    if (adminRepo.userExists(username))
    {
        string password;
        cout << "Password: ";
        cin >> password;
        if (adminRepo.validateAdmin(username, password))
        {
            cout << "Admin login successful.\n";
            AdminPanel().showMenu();
        }
        else
        {
            cout << "Invalid admin password.\n";
        }
        return;
    }

    if (StudentsData::existsInCSV(username))
    {
        cout << "Student ID found. Please enter your password:\n";
        string password;
        cout << "Password: ";
        cin >> password;

        Student *student = StudentsData::findStudentByIdAndPassword(username, password);
        if (student)
        {
            cout << "✔️ Student login successful.\n";
            StudentPanel panel;
            panel.setStudent(student);
            panel.showMenu();
        }
        else
        {
            cout << "Invalid student password.\n";
        }
        return;
    }

    cout << "Invalid username.\n";
}