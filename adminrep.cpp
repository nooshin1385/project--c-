#include "adminrepo.hpp"
#include "admin.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
using json = nlohmann::json;

AdminRepository::AdminRepository(const string &file) : filename(file)
{
    load();
}

void AdminRepository::checkAdminJson()
{
    ifstream in(filename);
    if (!in.good() || in.peek() == ifstream::traits_type::eof())
    {
        cout << "There is not any Admin!! Add an Admin!\n";
        string username, password;
        cout << "Enter new admin username: ";
        cin >> username;
        cout << "Enter new admin password: ";
        cin >> password;

        admins.push_back(Admin(username, password));
        save();
        cout << "Admin saved.\n";
    }
}

void AdminRepository::load()
{
    admins.clear();

    ifstream in(filename);
    if (!in.is_open() || in.peek() == ifstream::traits_type::eof())
        return;

    json j;
    in >> j;
    in.close();

    if (j.contains("admins") && j["admins"].is_array())
    {
        for (auto &item : j["admins"])
        {
            admins.push_back(Admin(item["username"], item["password"]));
        }
    }
}

void AdminRepository::save()
{
    json j;
    j["admins"] = json::array();

    for (auto &a : admins)
    {
        j["admins"].push_back({
            {"username", a.getUsername()},
            {"password", a.getPassword()}});
    }

    ofstream out(filename);
    out << setw(4) << j << endl;
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

bool AdminRepository::exists() const
{
    ifstream file(filename);
    return file.good();
}

bool AdminRepository::userExists(const string &username) const
{
    for (const auto &a : admins)
    {
        if (a.getUsername() == username)
            return true;
    }
    return false;
}

bool AdminRepository::validateAdmin(const string &username, const string &password) const
{
    for (const auto &a : admins)
    {
        if (a.getUsername() == username && a.getPassword() == password)
            return true;
    }
    return false;
}