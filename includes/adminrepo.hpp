#pragma once
#include "admin.hpp"
#include <vector>
#include <string>
using namespace std;

class AdminRepository
{
private:
    vector<Admin> admins;
    string filename;

public:
    AdminRepository(const string &file);

    void load();
    void save();

    void addAdmin(const Admin &admin);
    Admin *findByUsername(const string &username);
    bool exists();
    bool removeAdmin(const string &username);
    bool validateAdmin(const string& username, const string& password);
};