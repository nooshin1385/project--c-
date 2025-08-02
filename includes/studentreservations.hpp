#include <iostream>
#include "student.hpp"
#include "reservation.hpp"

using namespace std ; 
void save_student_reservations(const Student& student, const string& filename) {
    json j;
    vector<Reservation> reservations = student.getReserves();

    for (const auto& r : reservations) {
        j.push_back(r.to_json());
    }

    ofstream out(filename);
    if (out.is_open()) {
        out << j.dump(4);
        out.close();
        cout << "Reservations saved to " << filename << endl;
    } else {
        cerr << "Failed to open " << filename << " for writing." << endl;
    }
}
void load_student_reservations(Student& student, const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "No existing reservations found for student." << endl;
        return;
    }

    json j;
    in >> j;
    in.close();

    vector<Reservation> reservations;
    for (const auto& item : j) {
        Reservation r;
        r.from_json(item);
        reservations.push_back(r);
    }

    student.setreservation(reservations);
    cout << "Loaded " << reservations.size() << " reservations for student.\n";
}
