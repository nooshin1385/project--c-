#pragma once
#include <iostream>
#include "sessions.hpp"
#include "meal.hpp"
#include "student.hpp"
#include "studentreservations.hpp"
#include "shoppingcart.hpp"
using namespace std;

class StudentPanel
{
private:
    vector<Reservation> items;
    Student *loggedInStudent = nullptr;
    void LoginStudent()
    {
        string username, password;
        cout << "UserName : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;
        StudentSession::SessionManager *session = StudentSession::SessionManager::getinstance();
        session->Login_Session(username, password);
        Student *student = session->getCurrentStudent();
        if (student)
        {
            load_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");
        }
        else
        {
            cout << "Login failed or no student found.\n";
        }
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
        if (StudentSession::SessionManager::getinstance()->getstatus() != Authenticated)
        {
            cout << "please login first.\n";
            return;
        }
        vector<Meal> availableMeals = {
            Meal(1, "Salad", 15000, Breakfast, {}, Saturday),
            Meal(2, "Chicken", 30000, Lunch, {}, Saturday),
            Meal(3, "Pasta", 25000, Dinner, {}, Sunday),
            Meal(4, "Kebab", 40000, Lunch, {}, Monday)};

        cout << "\n--- Available Meals ---\n";
        for (auto &m : availableMeals)
        {
            cout << m.getmealid() << ". " << m.getmealname()
                 << " - Price: " << m.getprice()
                 << " - Day: " << static_cast<int>(m.getreserveday()) << "\n";
        }

        int mealId;
        cout << "Enter meal ID to add: ";
        cin >> mealId;

        auto it = find_if(availableMeals.begin(), availableMeals.end(),
                          [mealId](const Meal &m)
                          { return m.getmealid() == mealId; });

        if (it == availableMeals.end())
        {
            cout << "Invalid meal ID.\n";
            return;
        }

        Student *s = StudentSession::SessionManager::getinstance()->getCurrentStudent();
        Reservation r(100 + rand() % 900, Pending, new Meal(*it), nullptr, s);

        StudentSession::SessionManager::getinstance()->getShopping_Cart()->addReservation(r, s);
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

    void ViewReservations()
    {
        StudentSession::SessionManager *session = StudentSession::SessionManager::getinstance();
        Student *student = session->getCurrentStudent();

        if (!student)
        {
            cout << "No student logged in.\n";
            return;
        }

        string filename = "reservations_" + student->getStudentId() + ".json";
        ifstream in(filename);

        if (!in.is_open())
        {
            cout << "No reservations found for this student.\n";
            return;
        }

        json j;
        try
        {
            in >> j;
        }
        catch (const json::parse_error &e)
        {
            cout << "Error reading reservations file: " << e.what() << "\n";
            return;
        }
        in.close();

        if (j.empty())
        {
            cout << "No reservations available.\n";
            return;
        }

        cout << "\n----- Your Reservations -----\n";
        for (const auto &item : j)
        {
            Reservation r;
            r.from_json(item);

            cout << "Reservation ID: " << r.getReservationId() << "\n";
            if (r.getMeal())
                cout << "Meal: " << r.getMeal()->getmealname() << "\n";
            if (r.getdHall())
                cout << "Dining hall: " << r.getdHall()->getname() << "\n";

            cout << "Status: ";
            switch (r.getstatus())
            {
            case Pending:
                cout << "Pending";
                break;
            case Confirmed:
                cout << "Confirmed";
                break;
            case Cancelled:
                cout << "Cancelled";
                break;
            }
            time_t t = r.gettime();
            cout << "\nCreated at: " << ctime(&t);
            cout << "-------------------------\n";
        }
    }

    void removeReservationById()
    {
        Student *student = StudentSession::SessionManager::getinstance()->getCurrentStudent();
        if (!student)
        {
            cout << "Please login first.\n";
            return;
        }

        int id;
        cout << "Enter reservation ID to remove: ";
        cin >> id;

        if (StudentSession::SessionManager::getinstance()->getShopping_Cart()->removeItemById(id))
        {
            cout << "Reservation removed from cart.\n";
            return;
        }

        vector<Reservation> reserves = student->getReserves();
        bool found = false;
        for (auto &r : reserves)
        {
            if (r.getReservationId() == id && r.getstatus() == Confirmed)
            {
                float refund = r.getMeal()->getprice() * 0.8f;
                student->setBalance(student->getBalance() + refund);
                r.setStatus(Cancelled);
                found = true;
                cout << "Reservation cancelled. 20% penalty applied. Refund: " << refund << "\n";
                break;
            }
        }

        if (found)
        {
            student->setreservation(reserves);
            save_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");
        }
        else
        {
            cout << "Reservation ID not found.\n";
        }
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
    void setStudent(Student *s) { loggedInStudent = s; }
    const vector<Reservation> &getItems() const
    {
        return items;
    }

    void addItem(const Reservation &r)
    {
        items.push_back(r);
    }
    void confirmShoppingCart()
    {
        using namespace StudentSession;

        SessionManager *session = SessionManager::getinstance();
        Student *student = session->getCurrentStudent();
        ShoppingCart *cart = session->getShopping_Cart();

        if (!student || !cart)
        {
            cout << "No student or shopping cart found.\n";
            return;
        }

        if (cart->getreservation().empty())
        {
            cout << " Shopping cart is empty.\n";
            return;
        }

        cart->confirm(student);
        // save_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");
        cout << "CONFIRMING...\n";
        cout << "Cart items: " << cart->getreservation().size() << endl;
    }

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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                removeReservationById();
                break;
            case 8:
                increaseBalance();
                break;
            case 9:
                ViewReservations();
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

        Student *s = StudentSession::SessionManager::getinstance()->getCurrentStudent();
        if (!s)
        {
            cout << "No student found.\n";
            return;
        }

        Meal *meal = new Meal(mealId, name, price, static_cast<MealType>(type), sideItems, static_cast<Reserveday>(day));
        Reservation reservation(200 + rand() % 1000, Pending, meal, nullptr, s);

        StudentSession::SessionManager::getinstance()->getShopping_Cart()->addReservation(reservation, s);

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