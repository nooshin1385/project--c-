#ifndef STUDENTDATA_HPP
#define STUDENTDATA_HPP
#include <vector>
#include <string>
#include "student.hpp"
using namespace std;
class StudentsData
{
public:
    static vector<Student> loadFromCSV(const string &filename);
    static vector<Student> getStudents();
    static Student *findStudentByIdAndPassword(const string &studentId, const string &passwordHash);
    static bool existsInCSV(const string &studentId );
};

#endif