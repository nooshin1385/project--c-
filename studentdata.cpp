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
bool StudentsData::existsInCSV(const string &studentId)
{
    ifstream file("studentsCsvFile.csv");
    if (!file.is_open())
        return false;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string userId, id;

        getline(ss, userId, ',');
        getline(ss, id, ',');

        if (id == studentId)
        {
            return true;
        }
    }
    return false;
}
Student *StudentsData::findStudentByIdAndPassword(const string &studentId, const string &password)
{
    ifstream file("students.json");
    if (!file.is_open())
        return nullptr;

    json students;
    file >> students;

    for (auto &s : students)
    {
        if (s["StudentId"] == studentId)
        {
            string hashed = s["HashedPassword"];

            if (BCrypt::validatePassword(password, hashed))
            {
                Student *student = new Student();
                student->from_json(s);
                return student;
            }
            else
            {
                return nullptr;
            }
        }
    }
    return nullptr;
}
