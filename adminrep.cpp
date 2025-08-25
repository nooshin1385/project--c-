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
    ifstream file(filename);
    if (!file.is_open())
        return false;

    json admins;
    file >> admins;

    for (auto &a : admins)
    {
        if (a["username"] == username)
        {
            return true;
        }
    }
    return false;
}

bool AdminRepository::validateAdmin(const string &username, const string &password)
{
    ifstream file(filename);
    if (!file.is_open())
        return false;

    json admins;
    file >> admins;

    for (auto &a : admins)
    {
        if (a["username"] == username)
        {
            string hashed = a["password"];
            return BCrypt::validatePassword(password, hashed);
        }
    }
    return false;
}

void AdminRepository::addAdmin(const Admin &admin)
{
    json admins;
    ifstream infile(filename);
    if (infile.is_open())
    {
        infile >> admins;
    }
    infile.close();

    json newAdmin = {
        {"username", admin.getUsername()},
        {"password", admin.getPassword()}};

    admins.push_back(newAdmin);

    ofstream outfile(filename);
    outfile << admins.dump(4);
}