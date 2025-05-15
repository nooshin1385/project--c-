#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include"user.hpp"
#include "reservation.hpp"

using namespace std ;
class Student : public User
{
    int UserId;
    string StudentId;
    string Name;
    string Email;
    float Balance;
    bool IsActive;
    bool Hasreservation = false;     // there is any reserve or no ?
    vector<Reservation> reservation; // list for reserves
    int Phone;

public:
    Student()
    {
        UserId = 0;
        StudentId = "0000000000";
        Name = "ABC";
        Email = "abc@gmail.com";
        Balance = 0.0;
        IsActive = true;
        Hasreservation = true;
        Phone = 0;
    }
    Student(int user_id, string student_id, string _name, string _email, float _balance, bool is_active = true, vector<Reservation> _reservation, int _phone)
    {
        try
        {
            setUserId(to_string(user_id));
            setStudentId(student_id);
            setEmail(_email);
        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }

        StudentId = student_id;
        Name = _name;
        Email = _email;
        Balance = _balance;
        IsActive = is_active;
        reservation = _reservation;
        Phone = _phone;
    }
    Student &operator=(Student &ob)
    {
        if (this != &ob)
        {
            UserId = ob.UserId;
            StudentId = ob.StudentId;
            Name = ob.Name;
            Email = ob.Email;
            Balance = ob.Balance;
            IsActive = ob.IsActive;
            Hasreservation = ob.Hasreservation;
            Phone = ob.Phone;
        }
        return *this;
    }

    void setUserId(string _userID)
    {
        int count = 0;
        for (char c : _userID)
        {
            if (!isdigit(c))
            {
                throw "UserID must be just digits.";
            }
            count++;
        }

        if (count != 10)
        {
            throw "UserID must be exactly 10 digits.";
        }

        UserId = stoi(_userID);
    }
    void setStudentId(string _studentID)
    {
        int count = 0;
        for (char c : _studentID)
        {
            if (!isdigit(c))
            {
                throw "studentID must be just digits.";
            }
            count++;
        }
        if (count != 10)
            throw "studentID must be exactly 10 digits.";
        StudentId = _studentID;
    }
    void setName(string _name)
    {
        Name = _name;
    }
    void setEmail(string _email)
    {
        int i = _email.find('@');
        if (i == -1)
        {
            throw "your email address should have @ !";
        }
        int j = _email.find('.', i);
        if (j == -1)
        {
            throw "your email address should have . !";
        }
        Email = _email;
    }
    void setBalance(float _balance)
    {
        Balance = _balance;
        if (Balance < 0)
        {
            cout << "you are in debt and you cannot reserve food";
        }
    }
    void setIsActive(bool status)
    {
        IsActive = status;
    }
    void setHasrRservation(bool reservationstatus)
    {
        Hasreservation = reservationstatus;
    }
    void setreservation(vector<Reservation> _reservation)
    {
        reservation = _reservation;
    }
    void setphone(int _phone)
    {
        Phone = _phone;
    }
    int getUserId() { return UserId; }
    string getStudentId() { return StudentId; }
    string getName() { return Name; }
    string getEmail() { return Email; }
    float getBalance() { return Balance; }
    bool getIsActive() { return IsActive; }
    bool getHasReservation() { return Hasreservation; }
    vector<Reservation> getreservatin() { return reservation; }
    int getphone() { return Phone; }
    void ReserveMeal()
    {
        if (!IsActive)
        {
            cout << "you cannot reserve food because your account not active !" << endl;
        }
        else if (Balance < 0)
        {
            cout << "you are in debt and you can not reserve meal !" << endl;
        }
        else if (Hasreservation)
        {
            cout << "you already has a reservation !" << endl;
        }
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
    void AddReservatin(const Reservation &reservation)
    {
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
    bool Isactive()
    {
        return IsActive;
    }
    void Print() const
    {
        cout << "student information :" << endl;
        cout << "User ID :" << UserId << endl;
        cout << "Student ID :" << StudentId << endl;
        cout << "Name :" << Name << endl;
        cout << "Email :" << Email << endl;
        cout << "Balance :" << Balance << endl;
        cout << "Active :" << (IsActive ? "yes" : "no") << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
};