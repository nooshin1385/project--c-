#include <iostream>
#include "student.hpp"
#include "reservation.hpp"

using namespace std ; 
void save_student_reservations(const Student &student, const string &filename)
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    json j = json::array();
    for (const auto &r : student.getReserves())
    {
        j.push_back(r.to_json());
    }

    out << j.dump(4);
    out.close();
}
 void load_student_reservations(Student &student, const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        return;
    }

    if (in.peek() == ifstream::traits_type::eof())
    {
        return;
    }

    json j;
    try
    {
        in >> j;
    }
    catch (json::parse_error &e)
    {
        cerr << "JSON parse error in file: " << filename << " -> " << e.what() << endl;
        return;
    }
    in.close();

    vector<Reservation> loaded;
    for (const auto &item : j)
    {
        Reservation r;
        from_json(item, r);
        loaded.push_back(r);
    }
    student.setreservation(loaded);
}