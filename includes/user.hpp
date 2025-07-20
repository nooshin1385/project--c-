#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "include/bcrypt/BCrypt.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann ::json;

class User
{
    int UserId;
    string Name;
    string LastName;
    string HashedPassword;
    string Email;

public:
    User(int _userid, string _name, string _lastname, string _hpassword, string _email) : UserId(_userid), Name(_name), LastName(_lastname), HashedPassword(_hpassword), Email(_email) {}
    User() {}
    void setUserId(int _userid)
    {
        UserId = _userid;
    }
    void setName(string _name)
    {
        Name = _name;
    }
    void setLastName(string _lastname)
    {
        LastName = _lastname;
    }
    void setpassword(string _password)
    {
        HashedPassword = _password;
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
    int getuserid() const { return UserId; }
    string getname() const { return Name; }
    string getlastname() const { return LastName; }
    string getHashpassword() const { return HashedPassword; }
    string getemail() const { return Email; }
    virtual json to_json() const
    {
        return {
            {"UserId", UserId},
            {"Name", Name},
            {"LastName", LastName},
            {"Email", Email},
            {"HashedPassword", HashedPassword}

        };
    }
    virtual void from_json(const json &j)
    {

        UserId = j.at("UserId").get<int>();
        Name = j.at("Name").get<string>();
        LastName = j.at("LastName").get<string>();
        Email = j.at("Email").get<string>();
        HashedPassword = j.at("HashedPassword").get<string>();
    }
    virtual void print() const
    {
        cout << "useid :" << UserId << endl;
        cout << "Name & Lastname :"
             << Name << " " << LastName << endl;
        cout << "Email:" << Email << endl;
    }
    virtual void getType()
    {
        cout << "this is user." << endl;
    }
    bool checkpassword(const string &rawpassword) const
    {
        return BCrypt::validatePassword(rawpassword, HashedPassword);
    }
    virtual ~User() {}
};
