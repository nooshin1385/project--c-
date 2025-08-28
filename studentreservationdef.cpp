#include <iostream>
#include <string>
#include "student.hpp"
#include "reservation.hpp"
#include <fstream>
using namespace std;
using json = nlohmann::json;
void load_student_reservations(Student &student, const std::string &filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return;

    json j;
    in >> j;
    in.close();

    for (auto &item : j) {
        if (item["StudentId"] == student.getStudentId()) {
            student.setBalance(item["Balance"].get<double>());
            student.setHasRservation(item["Hasreservation"].get<bool>());
            break;
        }
    }
}
void save_student_reservations(const Student &student, const std::string &filename) {
    std::ifstream in(filename);
    json j;
    if (in.is_open()) {
        in >> j;
        in.close();
    }

    bool found = false;
    for (auto &item : j) {
        if (item["StudentId"] == student.getStudentId()) {
            item["Balance"] = student.getBalance(); 
            item["Hasreservation"] = student.getHasReservation();
            found = true;
            break;
        }
    }
    if (!found) {
        j.push_back({
            {"StudentId", student.getStudentId()},
            {"Balance", student.getBalance()},
            {"Hasreservation", student.getHasReservation()}
        });
    }

    std::ofstream out(filename);
    out << j.dump(4);
    out.close();
}
bool load_student_balance(Student &student, const std::string &path) {
    std::ifstream in(path);
    if (!in.is_open()) return false;

    json j;
    in >> j;
    in.close();

    for (auto &item : j) {
        if (item["StudentId"] == student.getStudentId()) {
            student.setBalance(item["Balance"].get<double>());
            return true;
        }
    }
    student.setBalance(0);
    return false;
}
void save_student_balance(const Student &student, const std::string &path) {
    std::ifstream in(path);
    json j;
    if (in.is_open()) {
        in >> j;
        in.close();
    }

    bool found = false;
    for (auto &item : j) {
        if (item["StudentId"] == student.getStudentId()) {
            item["Balance"] = student.getBalance();
            found = true;
            break;
        }
    }

    if (!found) {
        j.push_back({
            {"StudentId", student.getStudentId()},
            {"Balance", student.getBalance()}
        });
    }

    std::ofstream out(path);
    out << j.dump(4);
    out.close();
}

double getDisplayBalance(const Student &student) {
    return 0.0;
}
