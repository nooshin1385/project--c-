#include <iostream>
#include "sessions.hpp"
#include "meal.hpp"
#include "student.hpp"

using namespace std;
class StudentPanel
{
private:
    void LoginStudent()
    {
        string username, password;
        cout << "UserNmae :";
        cin >> username;
        cout << "Password :";
        cin >> password;

        StudentSession ::SessionManager ::getinstance()->Login_Session(username, password);
    }
    void ShowProfile()
    {
        auto *session = StudentSession ::SessionManager ::getinstance();
        if (session->getstatus() == Authenticated)
        {
            Student *s = session->getCurrentStudent();
            cout << "Welcom," << s->getname() << endl;
            cout << "Student ID: " << s->getStudentId() << endl;
            cout << "Email: " << s->getemail() << endl;
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
        Meal *m = new Meal(1, "Salad", 15000, Lunch, vector<string>{"Yogurt"}, Saturday);
        Reservation r(100, Pending, m, nullptr);
        StudentSession ::SessionManager ::getinstance()->getShopping_Cart()->addReservation(r);
        delete m;
    }
    void confirmShoppingCart()
    {
        auto *session = StudentSession::SessionManager::getinstance();
        if (session->getstatus() != Authenticated)
        {
            cout << "please login first!\n";
            return;
        }

        auto confirmed = session->getShopping_Cart()->coniform();
        Student *s = session->getCurrentStudent();

        for (const Reservation &r : confirmed)
        {
            s->AddReservation(r);
        }

        cout << "all items confirmed and moved from cart to student reservations.\n";
    }

    void checkBalance()
    {
        auto *s = StudentSession::SessionManager::getinstance()->getCurrentStudent();
        cout << "your current balance is: " << s->getBalance() << endl;
    }

    void logout()
    {
        StudentSession::SessionManager::getinstance()->logout();
    }

    void viewReservations()
    {
        Student *s = StudentSession::SessionManager::getinstance()->getCurrentStudent();
        for (const Reservation &r : s->getReserves())
        {
            r.printReservationinfo();
        }
    }

    void removeShoppingCartItem()
    {
        int id;
        cout << "enter reservation ID to remove from cart: ";
        cin >> id;

        StudentSession::SessionManager::getinstance()->getShopping_Cart()->removeReservation(id);
    }

    void increaseBalance()
    {
        float amount;
        cout << "enter amount to increase: ";
        cin >> amount;

        Student *s = StudentSession::SessionManager::getinstance()->getCurrentStudent();
        s->setBalance(s->getBalance() + amount);
        cout << "balance updated.\n";
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
            cout << "2.Veiw panel\n";
            cout << "3.Add meal to cart\n";
            cout << "4.Confirm resevation\n";
            cout << "5.Logout\n";
            cout << "6.Veiw shopping cart\n";
            cout << "7.Remove item from cart\n";
            cout << "8.Increase balance\n";
            cout << "9.Veiw reservations\n";
            cout << "10. Exit\n";
            cout << "Enter number of your choice :" << endl;
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "invalid inupt!! please enter a number \n";
                continue;
            }

            switch (choice)
            {
            case 1:
                LoginStudent();
                break;
            case 2:
                ShowProfile();
                break;
            case 3:
                AddMealtocart();
                break;
            case 4:
                confirmShoppingCart();
                break;
            case 5:
                logout();
                break;
            case 6:
                StudentSession::SessionManager::getinstance()->getShopping_Cart()->viewShoppingCartItems();
                break;
            case 7:
                removeShoppingCartItem();
                break;
            case 8:
                increaseBalance();
                break;
            case 9:
                viewReservations();
                break;
            case 10:
                Exitpanel();
                break;
            default:
                cout << "invalid choice! \n";
            }
        } while (choice != 10);
    }

    void ShowStudentInfo()
    {
        auto *session = StudentSession::SessionManager::getinstance();
        if (session->getstatus() == Authenticated)
        {
            Student *student = session->getCurrentStudent();
            student->print();
        }
        else
        {
            cout << "you should login first to see your information.\n";
        }
    }

    void addToShoppingCart()
    {
        if (StudentSession::SessionManager::getinstance()->getstatus() != Authenticated)
        {
            cout << "please login first.\n";
            return;
        }

        int mealId, price, day, type;
        string name;
        vector<string> sideItems;
        string item;
        int numSides;

        cout << "\nenter meal ID: ";
        cin >> mealId;
        cout << "enter meal name: ";
        cin >> name;
        cout << "enter meal price: ";
        cin >> price;

        cout << "enter meal type (1.breakfast, 2.lunch, 3.dinner, 4.dessert): ";
        cin >> type;

        cout << "enter reserved day (1.saturday ... 6.thursday): ";
        cin >> day;

        cout << "how many side items? ";
        cin >> numSides;
        for (int i = 0; i < numSides; ++i)
        {
            cout << "enter side item " << i + 1 << ": ";
            cin >> item;
            sideItems.push_back(item);
        }

        Meal *meal = new Meal(mealId, name, price, static_cast<MealType>(type), sideItems, static_cast<Reserveday>(day));
        Reservation reservation(200 + rand() % 1000, Pending, meal, nullptr);

        StudentSession::SessionManager::getinstance()->getShopping_Cart()->addReservation(reservation);
        cout << "meal added to cart successfully!\n";
    }

    void viewRecentTransactions()
    {
        auto *session = StudentSession::SessionManager::getinstance();
        if (session->getstatus() != Authenticated)
        {
            cout << "you must login to view transactions.\n";
            return;
        }

        cout << "this feature is not implemented yet.\n";
    }

    void cancelReservation(int reservationId)
    {
        auto *session = StudentSession::SessionManager::getinstance();
        if (session->getstatus() != Authenticated)
        {
            cout << "you must be logged in to cancel a reservation.\n";
            return;
        }

        Student *student = session->getCurrentStudent();
        vector<Reservation> reservations = student->getReserves();

        bool found = false;

        for (Reservation &r : reservations)
        {
            if (r.getReservationId() == reservationId)
            {
                if (r.CancelReservation())
                {
                    cout << "reservation " << reservationId << " cancelled successfully.\n";
                }
                else
                {
                    cout << "reservation cant be cancelled (already cancelled?).\n";
                }
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "reservation ID not found.\n";
        }
    }
    void Exitpanel()
    {
        cout << "\n exiting student panel ...\n";
    }
};