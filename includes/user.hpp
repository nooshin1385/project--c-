#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <json.hpp>
using namespace std;
using json = nlohmann ::json;

class User
{
    int UserId;
    string Name;
    string LastName;
    string HashedPassword;

public:
    User(int _userid, string _name, string _lastname, string _hpassword) : UserId(_userid), Name(_name), LastName(_lastname), HashedPassword(_hpassword) {}
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
    int getuserid() const { return UserId; }
    string getname() const { return Name; }
    string getlastname() const { return LastName; }
    string getpassword() const { return HashedPassword; }
    virtual json to_json() const
    {
        return {
            {"UserId", UserId},
            {"Name", Name},
            {"LastName", LastName}};
    }
    virtual void from_json(const json &j)
    {

        UserId = j.at("UserId").get<int>();
        Name = j.at("Name").get<string>();
        LastName = j.at("LastName").get<string>();
    }
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
