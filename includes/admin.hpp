#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "student.hpp"
#include "meal.hpp"
#include "dininghall.hpp"

class Admin {
private:
    string username;
    string password;

public:
    Admin() {}
    Admin(const string& u, const string& p) : username(u), password(p) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    void setUsername(const string& u) { username = u; }
    void setPassword(const string& p) { password = p; }
};