#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "student.hpp"
#include "meal.hpp"
#include "dininghall.hpp"

class Admin : public User
{
public:
    Admin()
    {
    }
    void getType()
    {
        cout << "this is Admin ." << endl;
    }
    void print() const
    {

        User ::print();
    }
};