#pragma once
#include "student.hpp"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

inline void saveAllStudents(const vector<Student>& students, const string& filename = "students.json") {
    json j;
    for (const auto& s : students) {
        j.push_back(s.to_json());
    }

    ofstream out(filename);
    if (out.is_open()) {
        out << j.dump(4);
        out.close();
        cout << "Students saved to " << filename << endl;
    } else {
        cerr << "Failed to save students to " << filename << endl;
    }
}

inline vector<Student> loadAllStudents(const string& filename = "students.json") {
    vector<Student> students;
    ifstream in(filename);
    if (in.is_open()) {
        json j;
        in >> j;
        in.close();
        for (const auto& item : j) {
            Student s;
            s.from_json(item);
            students.push_back(s);
        }
    } else {
        cerr << "File not found, starting with empty student list.\n";
    }

    return students;
}