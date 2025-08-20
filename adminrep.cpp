#include "adminrepo.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

AdminRepository::AdminRepository(const string &file) : filename(file)
{
    load();
}

void AdminRepository::load()
{
    admins.clear();
    ifstream in(filename);
    if (!in.is_open())
        return;

    json j;
    in >> j;
    in.close();

    for (auto &item : j)
    {
        admins.push_back(Admin(item["username"], item["password"]));
    }
}

void AdminRepository::save()
{
    json j;
    for (auto &a : admins)
    {
        j.push_back({{"username", a.getUsername()}, {"password", a.getPassword()}});
    }

    ofstream out(filename);
    out << j.dump(4);
    out.close();
}

void AdminRepository::addAdmin(const Admin &admin)
{
    admins.push_back(admin);
    save();
}

Admin *AdminRepository::findByUsername(const string &username)
{
    for (auto &a : admins)
    {
        if (a.getUsername() == username)
            return &a;
    }
    return nullptr;
}

bool AdminRepository::exists()
{
    return !admins.empty();
}

bool AdminRepository::removeAdmin(const string &username)
{
    for (auto it = admins.begin(); it != admins.end(); ++it)
    {
        if (it->getUsername() == username)
        {
            admins.erase(it);
            save();
            return true;
        }
    }
    return false;
}
bool AdminRepository::validateAdmin(const string &username, const string &password)
{
    for (auto &a : admins)
    {
        if (a.getUsername() == username && a.getPassword() == password)
        {
            return true;
        }
    }
    return false;
}