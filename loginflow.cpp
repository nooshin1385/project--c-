#include "loginflow.hpp"
#include "adminrepo.hpp"
#include "studentdata.hpp"
#include "studentpanel.hpp"
#include "adminpanel.hpp"
#include "logger.hpp"
#include <iostream>
using namespace std;

void LoginFlow::login()
{
    Logger logger("system.log");
    AdminRepository adminRepo("admin.json");

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
            logger.log("Admin login successful: " + username);
            AdminPanel().showMenu();
        }
        else
        {
            cout << "Invalid admin password.\n";
            logger.logError("Invalid admin password attempt for admin: " + username);
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
            cout << "Student login successful.\n";
            logger.log("Student login successful: " + username);
            StudentPanel panel;
            panel.setStudent(student);
            panel.showMenu();
        }
        else
        {
            cout << "Invalid student password.\n";
            logger.logError("Invalid student password attempt for student: " + username);
        }
        return;
    }

    cout << "Invalid username.\n";
    logger.logError("Invalid username attempt: " + username);
}