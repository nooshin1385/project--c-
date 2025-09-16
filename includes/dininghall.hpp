#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class DiningHall
{
    int HallID;
    string Name;
    string Address;
    int Capacity;
    int CurrentOccupancy;

public:
    DiningHall()
    {
        HallID = 0;
        Name = "";
        Address = "";
        Capacity = 0;
        CurrentOccupancy = 0;
    }
    DiningHall(int _HallID, string _Name, string _Address, int _Capacity)
    {
        HallID = _HallID;
        Name = _Name;
        Address = _Address;
        Capacity = _Capacity;
        CurrentOccupancy = 0;
    }

    void sethallid(int _hallID) { HallID = _hallID; }
    void setname(string _name) { Name = _name; }
    void setaddress(string _address) { Address = _address; }
    void setcapacity(int _capacity) { Capacity = _capacity; }
    void setoccupancy(int occ) { CurrentOccupancy = occ; }

    int gethallid() const { return HallID; }
    string getname() const { return Name; }
    string getaddress() const { return Address; }
    int getcapacity() const { return Capacity; }
    int getoccupancy() const { return CurrentOccupancy; }

    string getStatusColor() const
    {
        if (Capacity == 0)
            return "\033[90m●\033[0m";
        double usage = (double)CurrentOccupancy / Capacity;
        if (usage < 0.5)
            return "\033[32m●\033[0m";
        else if (usage < 0.8)
            return "\033[33m●\033[0m";
        else
            return "\033[31m●\033[0m";
    }

    bool isFull() const
    {
        return CurrentOccupancy >= Capacity;
    }

    bool reserveSeat()
    {
        if (!isFull())
        {
            CurrentOccupancy++;
            return true;
        }
        return false;
    }

    void printdininghallinfo() const
    {
        cout << "Dining hall info :" << endl;
        cout << "ID : " << HallID << endl;
        cout << "Name : " << Name << endl;
        cout << "Address : " << Address << endl;
        cout << "Capacity : " << Capacity << endl;
        cout << "Current Occupancy : " << CurrentOccupancy << endl;
        cout << "Status : " << getStatusColor()
             << " (" << CurrentOccupancy << "/" << Capacity << ")"
             << endl;
        cout << "----------------------" << endl;
    }

    json to_json() const
    {
        return {
            {"HallID", HallID},
            {"Name", Name},
            {"Address", Address},
            {"Capacity", Capacity},
            {"CurrentOccupancy", CurrentOccupancy}};
    }

    void from_json(const json &j)
    {
        HallID = j.at("HallID").get<int>();
        Name = j.at("Name").get<string>();
        Address = j.at("Address").get<string>();
        Capacity = j.at("Capacity").get<int>();
        CurrentOccupancy = j.value("CurrentOccupancy", 0);
    }
    vector<DiningHall> loadDiningHalls(const string &filename)
    {
        vector<DiningHall> halls;
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return halls;
        }

        json j;
        file >> j;

        for (auto &item : j)
        {
            DiningHall hall;
            hall.from_json(item);
            halls.push_back(hall);
        }

        return halls;
    }
};