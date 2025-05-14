#include <iostream>
#include <ctime>
#include <vector>

using namespace std;
class User
{
    int UserId;
    string Name;
    string LastName;
    string HashedPassword;

public:
    User(int _userid, string _name, string _lastname, string _hpassword) : UserId(_userid), Name(_name), LastName(_lastname), HashedPassword(_hpassword) {}
    virtual void print() const;
    virtual void getType()
    {
        cout << "this is user." << endl;
    }
    User() {}
};
