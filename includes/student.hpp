#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "user.hpp"
#include "reservation.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Student : public User
{
    string StudentId;
    float Balance;
    bool IsActive;
    bool Hasreservation = false;
    vector<Reservation> reservation;
    string Phone;

public:
    Student(string student_id, float _balance, bool is_active = true, vector<Reservation> _reservation = {}, string _phone = "")
    {
        try
        {
            setStudentId(student_id);
        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }

        Balance = _balance;
        IsActive = is_active;
        reservation = _reservation;
        Phone = _phone;
    }
    Student(int userId,
            const string &firstName,
            const string &lastName,
            const string &passwordHash,
            const string &email,
            const string &studentId,
            const string &phone,
            float balance = 0)
        : User(userId, firstName, lastName, passwordHash, email),
          StudentId(studentId),
          Phone(phone),
          Balance(balance) {}

    Student() : User(), Balance(0) {}
    Student &operator=(const Student &ob)
    {
        if (this != &ob)
        {
            StudentId = ob.StudentId;
            Balance = ob.Balance;
            IsActive = ob.IsActive;
            Hasreservation = ob.Hasreservation;
            Phone = ob.Phone;
            reservation = ob.reservation;
        }
        return *this;
    }

    json to_json() const override
    {
        json j = User::to_json();
        j["StudentId"] = StudentId;
        j["Balance"] = Balance;
        j["IsActive"] = IsActive;
        j["Hasreservation"] = Hasreservation;
        j["Phone"] = Phone;
        j["reservations"] = json::array();
        for (const auto &r : reservation)
        {
            j["reservations"].push_back(r.to_json());
        }

        return j;
    }

    void from_json(const json &j) override
    {
        User::from_json(j);
        StudentId = j.at("StudentId").get<string>();
        Balance = j.at("Balance").get<float>();
        IsActive = j.at("IsActive").get<bool>();
        Hasreservation = j.at("Hasreservation").get<bool>();
        Phone = j.at("Phone").get<string>();
        if (j.contains("HashedPassword"))
            setpassword(j.at("HashedPassword").get<string>());

        reservation.clear();
        if (j.contains("reservations") && j["reservations"].is_array())
        {
            for (const auto &item : j["reservations"])
            {
                Reservation r;
                r.from_json(item);
                reservation.push_back(r);
            }
        }
    }

    void setStudentId(string _studentID)
    {
        int count = 0;
        for (char c : _studentID)
        {
            if (!isdigit(c))
                throw "studentID must be just digits.";
            count++;
        }
        if (count != 10)
            throw "studentID must be exactly 10 digits.";
        StudentId = _studentID;
    }

    void setBalance(float _balance)
    {
        Balance = _balance;
        if (Balance < 0)
            cout << "you are in debt and you cannot reserve food";
    }

    void setIsActive(bool status) { IsActive = status; }
    void setHasRservation(bool reservationstatus) { Hasreservation = reservationstatus; }
    void setreservation(const vector<Reservation> &_reservation) { reservation = _reservation; }
    void setphone(string _phone) { Phone = _phone; }

    string getStudentId() const { return StudentId; }
    float getBalance() const { return Balance; }
    bool getIsActive() const { return IsActive; }
    bool getHasReservation() const { return Hasreservation; }
    vector<Reservation> getReserves() const { return reservation; }
    string getphone() { return Phone; }

    void ReserveMeal()
    {
        if (!IsActive)
            cout << "you cannot reserve food because your account not active !" << endl;
        else if (Balance < 0)
            cout << "you are in debt and you can not reserve meal !" << endl;
        else if (Hasreservation)
            cout << "you already has a reservation !" << endl;
        else
        {
            Hasreservation = true;
            cout << "your meal reserved successfully ." << endl;
        }
    }

    bool CancelReservation()
    {
        if (!Hasreservation)
        {
            cout << "you do not have any reserve !" << endl;
            return false;
        }
        else
        {
            Hasreservation = false;
            cout << "your reserve has cancelled" << endl;
            return true;
        }
    }

    void AddReservation(const Reservation &r)
    {
        reservation.push_back(r);
        Hasreservation = true;
    }

    void Activate()
    {
        IsActive = true;
        cout << "student account is active .\n";
    }
    void Deactivate()
    {
        IsActive = false;
        cout << "student account is deactive .\n";
    }

    void print() const
    {
        User::print();
        cout << "student information :" << endl;
        cout << "Student ID :" << StudentId << endl;
        cout << "Balance :" << Balance << endl;
        cout << "Active :" << (IsActive ? "yes" : "no") << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
};
inline void to_json(json &j, const Student &s)
{
    j = s.to_json();
}

inline void from_json(const json &j, Student &s)
{
    s.from_json(j);
}
inline void save_student_to_file(const Student &student, const string &filename)
{
    json j = student.to_json();
    ofstream out(filename);
    if (out.is_open())
    {
        out << j.dump(4);
        out.close();
    }
}

inline Student load_student_from_file(const string &filename)
{
    ifstream in(filename);
    Student s;
    if (in.is_open())
    {
        json j;
        in >> j;
        s.from_json(j);
        in.close();
    }
    return s;
}