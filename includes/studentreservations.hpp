#pragma once

#include "student.hpp"
#include <string>
using namespace std;

void save_student_reservations(const Student &student, const string &filename);
void load_student_reservations(Student &student, const string &filename);
void save_student_balance(const Student &student, const string &path);
bool load_student_balance(Student &student, const string &path);
