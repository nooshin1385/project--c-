#include <iostream>
#include "sessions.hpp"
#include "meal.hpp"

using namespace std;
class StudentPanel
{
private:
    void LoginStudent()
    {
        string usesrname, password;
        cout << "UserNmae :";
        cin >> usesrname;
        cout << "Password :";
        cin >> password;

        StudentSession ::SessionManager ::getinstance()->Login_Session(usesrname, password);
    }
    void ShowProfile()
    {
        auto *session = StudentSession ::SessionManager ::getinstance();
        if (session->getstatus() == Authenticated)
        {
            Student *s = session->getCurrentStudent();
            cout << "Welcom," << s->getname() << endl;
            cout << "Balance :" << s->getBalance() << endl;
        }
        else
        {
            cout << "You are not Login!" << endl;
        }
    }
    void AddMealtocart()
    {
        if (StudentSession ::SessionManager ::getinstance()->getstatus() != Authenticated)
        {
            cout << " Please first Login!\n";
            return;
        }
        Meal m(1, string("Salad"), 15000, Lunch, vector<string>(), Saturday);
        StudentSession ::SessionManager ::getinstance()->getShopping_Cart()->addReservation();
    }

public:
    StudentPanel() {}

    void Action(int)
    {
    }
    void showMenu()
    {
        int choice;
        do
        {
            cout << "\n----- STUDENT PANEL -----\n";
            cout << "1.Login\n";
            cout << "2.Veiw Panel\n";
            cout << "3.Add Meal to Cart\n";
            cout << "4.Confirm Resevation\n";
            cout << "5.Logout\n";
            cout << "6.Exit\n";
            cout << "Enter number of your choice :" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                LoginStudent();

            default:
                break;
            }
        }
    }
    void showStudentInfo()
    {
    }

    void checkBalance()
    {
    }

    void viewReservations()
    {
    }

    void addToShoppingCart();

    void confirmShoppingCart();

    void removeShoppingCartItem()
    {
    }

    void increaseBalance()
    {
    }

    void viewRecentTransactions();

    void cancelReservation(int);
    void exit()
    {
    }
};