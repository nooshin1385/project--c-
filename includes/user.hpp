#pragma once
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;
class User
{
    int UserId;
    string Name;
    string LastName;
    string HashedPassword;

public:
    User(int _userid, string _name, string _lastname, string _hpassword) : UserId(_userid), Name(_name), LastName(_lastname), HashedPassword(_hpassword) {}
    User() {}
    void setuserId(int _userid)
    {
        UserId = _userid;
    }
    void setname(string _name)
    {
        Name = _name;
    }
    void setlastname(string _lastname)
    {
        LastName = _lastname;
    }
    void setpassword(string _password)
    {
        HashedPassword = _password;
    }
    int getuserid() const { return UserId; }
    string getname() const { return Name; }
    string getlastname() const { return LastName; }
    string getpassword() const { return HashedPassword; }
    virtual void print() const
    {
        cout << "useid :" << UserId << endl;
        cout << "Name & Lastname :"
             << Name << " " << LastName << endl;
    }
    virtual void getType()
    {
        cout << "this is user." << endl;
    }
};
