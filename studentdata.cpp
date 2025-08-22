#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "studentdata.hpp"
#include "student.hpp"
#include "user.hpp"
#include "include/bcrypt/BCrypt.hpp"

using namespace std;

vector<Student> StudentsData::loadFromCSV(const string &filename)
{
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string userId, studentId, firstName, lastName, passwordHash, email, phone;

        getline(ss, userId, ',');
        getline(ss, studentId, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, passwordHash, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        // ساخت شی Student با داده‌ها
        Student s(stoi(userId), firstName, lastName, passwordHash, email, studentId, phone, 100000);
        students.push_back(s);
    }

    file.close();
    return students;
}

vector<Student> StudentsData::getStudents()
{
    return loadFromCSV("studentsCsvFile.csv");
}

Student *StudentsData::findStudentByIdAndPassword(const string &studentId, const string &rawPassword)
{
    static vector<Student> students = loadFromCSV("studentsCsvFile.csv");

    for (auto &s : students)
    {
        if (s.getStudentId() == studentId && BCrypt::validatePassword(rawPassword, s.getHashpassword()))
        {
            return &s;
        }
    }
    return nullptr;
}