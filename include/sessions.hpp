#include <iostream>
using namespace std;
enum Sessionstatus
{
    Authenticated,
    Anonymous
};
class SessionsBase
{
protected:
    time_t Created_At;     // zaman shro jalase
    time_t LastTimeLogin;  // zaman akharin vorod
    Sessionstatus Statuse; // vasiat jalase

public:
    SessionsBase()
    {
        Created_At = time_t(nullptr);
        LastTimeLogin = 0;
        Statuse = Anonymous;
    }

    virtual void load_Session() = 0;
    virtual void save_Session() = 0;
    virtual void Login_Seesion(string username, string password) = 0;
    virtual void logout() = 0;
    void setcreatedat(time_t T)
    {
        if (T <= time(nullptr))
        {
            Created_At = T;
        }
        else
        {
            cout << "time is in future!" << endl;
        }
    }
    void settimeLogin(time_t t)
    {
        if (t <= time(nullptr) && t >= Created_At)
        {
            LastTimeLogin = t;
        }
        else
        {
            cout << "this time invalid" << endl;
        }
    }
    void setSessionstatus(Sessionstatus _status)
    {
        if (_status == Sessionstatus::Authenticated ||
            _status == Sessionstatus::Anonymous)
        {
            Statuse = _status;
        }
        else
        {
            cout << "Sessionstatus is not invalid " << endl;
        }
    }
    time_t getCreatedAt() const
    {
        return Created_At;
    }
    time_t getLastTimeLogin() const
    {
        return LastTimeLogin;
    }
    Sessionstatus getstatus() const
    {
        return Statuse;
    }
};