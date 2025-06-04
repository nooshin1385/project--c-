#include <iostream>
#include "student.hpp"
#include "shoppingcart.hpp"
#include "admin.hpp"
using namespace std;
enum Sessionstatus
{
    Authenticated,
    Anonymous
};
class SessionBase
{
protected:
    time_t Created_At;     // zaman shro jalase
    time_t LastTimeLogin;  // zaman akharin vorod
    Sessionstatus Statuse; // vasiat jalase

public:
    SessionBase()
    {
        Created_At = time_t(nullptr);
        LastTimeLogin = 0;
        Statuse = Anonymous;
    }

    virtual void load_Session() = 0;
    virtual void save_Session() = 0;
    virtual void Login_Session(string username, string password) = 0;
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
    void setlasttimeLogin(time_t t)
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
namespace StudentSession
{
    class SessionManager : public SessionBase
    {
        Student *CurrentStudent;
        ShoppingCart *Shopping_Cart;
        int StudentID;
       // static SessionManager *instace;

    public:
        SessionManager()
        {
            CurrentStudent = nullptr;
            Shopping_Cart = nullptr;
            StudentID = 0;
            setSessionstatus(Sessionstatus ::Anonymous);
            setcreatedat(time(nullptr));
        }
        //   StudentManager() {};
        void load_Session() override{

        }
        void save_Session() override{

        }
        void Login_Session(string username, string password) override
        {
            CurrentStudent = new Student();
            StudentID = stoi(username);
            setSessionstatus(Authenticated);
            setlasttimeLogin(time(nullptr));
            cout << "Student" << username << "Logged in .\n";
        }
        void logout() override{
            delete CurrentStudent ;
            delete Shopping_Cart ;
            CurrentStudent = nullptr; 
            Shopping_Cart = nullptr ;
            StudentID = 0 ;
            setSessionstatus(Anonymous) ;
            cout << "Logged out.\n" ;
        }
     

        Student *getCurrentStudent() const
        {
            return CurrentStudent;
        }
        ShoppingCart *getShopping_Cart() const
        {
            return Shopping_Cart;
        }
        static SessionManager *getinstance()
        {
            if (!instance)
            {
                instance = new SessionManager();
                return instance;
            }
        }
    };

}
namespace AdminSession
{
    class SessionManager : public SessionBase
    {
        Admin *CurrentAdmin;
        int AdminID;

    public:
        void load_Session() override;
        void save_Session() override;
        void Login_Session(string, string) override;
        void logout() override;
        Admin *getCurrentAdmin() const;
        static SessionManager *instance;
        static SessionManager *getinstance()
        {
            if (!instance)
            {
                instance = new SessionManager();
                return instance;
            }
        }
    };
}