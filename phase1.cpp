#include <iostream>
using namespace std;

class Student
{
    int UserId;
    string StudentId;
    string Name;
    string Email;
    float Balance;
    bool IsActive;

public:
    Student(int user_id, string student_id, string _name, string _email, float _balance, bool is_active = true)
    {
        try
        {
            setUserId(to_string(user_id));
            setstudentid(student_id);
            setemail(_email);
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
    void setstudentid(string _studentID)
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
    void setname(string _name)
    {
        Name = _name;
    }
    void setemail(string _email)
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
    void setbalance(float _balance)
    {
        Balance = _balance;
        bool credit;
        if (Balance < 0)
        {
            credit = true;
            cout << "you are in debt and you cannot reserve food";
        }
        else
        {
            credit = false;
        }
    }
};