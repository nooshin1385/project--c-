#include "loginflow.hpp"
#include "studentpanel.hpp"
#include "adminpanel.hpp"
#include <iostream>

using namespace std;

void LoginFlow::login()
{
    cout << "Enter username (studentId or admin username): ";
    string username;
    cin >> username;

    cout << "Enter password: ";
    string password;
    cin >> password;
    AdminRepository adminRepo("admins.json");
    if (adminRepo.exists())
    {
        if (adminRepo.validateAdmin(username, password))
        {
            cout << "Admin login successful.\n";
            AdminPanel().showMenu();
            return;
        }
    }

   Student* student = StudentsData::findStudentByIdAndPassword(username, password);

if (student) {
    cout << "Student login successful.\n";
    StudentPanel panel;         
    panel.setStudent(student);   
    panel.showMenu();           
    return;
}

    cout << "Invalid username or password.\n";
}