#pragma once

#include "student.hpp"
#include <string>
using namespace std;

 void save_student_reservations(const Student& student, const string& filename);
 void load_student_reservations(Student& student, const string& filename);
