#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
class DiningHall
{
    int HallID;
    string Name;
    string Address;
    int Capacity;

public:
    DiningHall()
    {
        HallID = 0;
        Name = "";
        Address = "";
        Capacity = 0;
    }
    DiningHall(int _HallID, string _Name, string _Address, int _Capacity)
    {
        HallID = _HallID;
        Name = _Name;
        Address = _Address;
        Capacity = _Capacity;
    }
    void sethallid(int _hallID)
    {
        HallID = _hallID;
    }
    void setname(string _name)
    {
        Name = _name;
    }
    void setaddress(string _address)
    {
        Address = _address;
    }
    void setcapacity(int _capacity)
    {
        Capacity = _capacity;
    }
    int gethallid() { return HallID; }
    string getname() { return Name; }
    string getaddress() { return Address; }
    int getcapacity() { return Capacity; }

    void printdininghallinfo()
    {
        cout << "Dining hall info :" << endl;
        cout << "ID :" << HallID << endl;
        cout << "Name :" << Name << endl;
        cout << "Address :" << Address << endl;
        cout << "Capacity :" << Capacity << endl;
        cout << "----------------------" << endl;
    }
};