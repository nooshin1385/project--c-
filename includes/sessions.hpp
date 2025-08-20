#pragma once
#include <iostream>
#include "student.hpp"
#include "shoppingcart.hpp"
#include "admin.hpp"
#include "studentsdata.hpp"
#include "studentreservations.hpp"
using namespace std;
class ShoppingCart;
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
    virtual ~SessionBase() {}

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
        static SessionManager *instance;
        vector<Student> allStudents;
        SessionManager()
        {
            CurrentStudent = nullptr;
            Shopping_Cart = nullptr;
            StudentID = 0;
            setSessionstatus(Sessionstatus ::Anonymous);
            setcreatedat(time(nullptr));
        }

    public:
        static SessionManager *getinstance()
        {
            if (!instance)
            {
                instance = new SessionManager();
            }
            return instance;
        }

        //   StudentManager() {};
        void load_Session() override
        {
            allStudents = loadAllStudents();
        }
        void save_Session() override
        {
            saveAllStudents(allStudents);
        }

        void Login_Session(string username, string password) override
        {
            if (CurrentStudent)
                delete CurrentStudent;
            if (Shopping_Cart)
                delete Shopping_Cart;

            for (const auto &s : allStudents)
            {
                if (s.getStudentId() == username && BCrypt::validatePassword(password, s.getHashpassword()))
                {
                    CurrentStudent = new Student(s);
                    Shopping_Cart = new ShoppingCart();
                    setSessionstatus(Sessionstatus::Authenticated);
                    setlasttimeLogin(time(nullptr));

                    cout << "Welcome, " << CurrentStudent->getname() << " " << CurrentStudent->getlastname() << " logged in.\n";
                    load_student_reservations(*CurrentStudent, "reservations_" + username + ".json");
                    return;
                }
            }

            cout << "Login failed: user not found or wrong password.\n";
        }
        void logout() override
        {
            if (CurrentStudent)
            {
                save_student_reservations(*CurrentStudent, "reservations_" + CurrentStudent->getStudentId() + ".json");
                delete CurrentStudent;
            }

            if (Shopping_Cart)
                delete Shopping_Cart;

            CurrentStudent = nullptr;
            Shopping_Cart = nullptr;
            StudentID = 0;
            setSessionstatus(Anonymous);

            cout << "Logged out.\n";
        }

        Student *getCurrentStudent() const
        {
            return CurrentStudent;
        }
        ShoppingCart *getShopping_Cart() const
        {
            return Shopping_Cart;
        }
    };
    SessionManager *StudentSession ::SessionManager ::instance = nullptr;

}
namespace AdminSession
{
    class SessionManager : public SessionBase
    {
        Admin *CurrentAdmin;
        string AdminID;
        static inline SessionManager *instance = nullptr;

        SessionManager()
        {
            CurrentAdmin = nullptr;
            AdminID = "";
            setSessionstatus(Sessionstatus::Anonymous);
            setcreatedat(time(nullptr));
        }

    public:
        static SessionManager *getinstance()
        {
            if (!instance)
                instance = new SessionManager();
            return instance;
        }

        void load_Session() override
        {
            cout << "admin session loaded.\n";
        }

        void save_Session() override
        {
            cout << "admin session saved.\n";
        }

        void Login_Session(string username, string /*password*/) override
        {
            CurrentAdmin = new Admin();
            AdminID = username;
            setSessionstatus(Sessionstatus::Authenticated);
            setlasttimeLogin(time(nullptr));
            cout << "Admin " << username << " logged in.\n";
        }

        void logout() override
        {
            delete CurrentAdmin;
            CurrentAdmin = nullptr;
            AdminID = "";
            setSessionstatus(Sessionstatus::Anonymous);
            cout << "admin logged out.\n";
        }

        Admin *getCurrentAdmin() const
        {
            return CurrentAdmin;
        }
    };

   // SessionManager *SessionManager::instance = nullptr;
}
