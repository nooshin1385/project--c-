#pragma once
#include <iostream>
#include <vector>
#include "reservation.hpp"
#include "json.hpp"
#include "student.hpp"
#include "studentreservations.hpp"
using namespace std;
using json = nlohmann ::json;
class ShoppingCart
{
    vector<Reservation> reservation;

public:
    void confirm(Student *student);
    bool removeReservation(Student *student,int reservationID);
    bool addReservation(const Reservation &r, const Student *student);
    void removeConfirmedReservation(int reservationID, Student *student, bool hardDelete);
    void removeFromCart(int reservationId);
    /* void confirm(Student *student)
     {
         if (!student)
         {
             cout << "No student logged in.\n";
             return;
         }

         if (reservation.empty())
         {
             cout << "Cart is empty.\n";
             return;
         }

         float total = 0;
         for (auto &r : reservation)
         {
             if (r.getMeal())
                 total += r.getMeal()->getprice();
         }

         if (student->getBalance() < total)
         {
             cout << "Not enough balance to confirm reservations.\n";
             cout << "Please increase your balance (Option 8).\n";
             return;
         }

         vector<Reservation> currentReserves = student->getReserves();

         for (auto &r : reservation)
         {
             r.setStatus(Confirmed);
             r.setReservationID(time(nullptr));
             currentReserves.push_back(r);
             student->setBalance(student->getBalance() - r.getMeal()->getprice());
         }

         student->setreservation(currentReserves);
         save_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");

         reservation.clear();

         cout << "Reservations confirmed and saved.\n";
         cout << "Remaining balance: " << student->getBalance() << "\n";
     }*/
    /* void removeReservation(int ID)
      {
          auto it =
              remove_if(reservation.begin(), reservation.end(), [ID](const Reservation &r)
                        { return r.getReservationId() == ID; });
          if (it != reservation.end())
          {
              reservation.erase(it, reservation.end());
              cout << "reservaes removed from cart.\n";
          }
          else
          {
              cout << " reservation IDnot found .\n";
          }
      }*/
    bool removeItemById(int id)
    {
        auto it = remove_if(reservation.begin(), reservation.end(),
                            [id](const Reservation &r)
                            {
                                return r.getReservationId() == id;
                            });

        if (it != reservation.end())
        {
            reservation.erase(it, reservation.end());
            return true;
        }
        return false;
    }
    void viewShoppingCartItems()
    {
        if (reservation.empty())
        {
            cout << "shopping cart is empty. \n";
            return;
        }
        else
        {
            cout << "----Shopping Cart Itemes: ---\n";
            for (const Reservation &r : reservation)
            {
                r.printReservationinfo();
            }
        }
    }
    void clearcart()
    {
        reservation.clear();
        cout << "Shopping cart is clear now.\n";
    }
    const vector<Reservation> &getreservation() const
    {
        return reservation;
    }
    vector<Reservation> coniform()
    {
        vector<Reservation> coniformed = reservation;
        clearcart();
        return coniformed;
    }
    json to_json() const
    {
        json j;
        for (const auto &r : reservation)
        {
            j.push_back(r.to_json());
        }
        return j;
    }
    void from_json(const json &j)
    {
        reservation.clear();
        for (const auto &item : j)
        {
            Reservation r;
            r.from_json(item);
            reservation.push_back(r);
        }
    }
};
inline void ShoppingCart::confirm(Student *student)
{
    if (!student)
    {
        cout << " No student logged in.\n";
        return;
    }
    if (reservation.empty())
    {
        cout << "Cart is empty.\n";
        return;
    }

    vector<Reservation> current = student->getReserves();
    vector<Reservation> toConfirm;
    float total = 0;

    auto sameMealDay = [](const Reservation &a, const Reservation &b)
    {
        return a.getMeal() && b.getMeal() &&
               a.getMeal()->getmealid() == b.getMeal()->getmealid() &&
               a.getMeal()->getreserveday() == b.getMeal()->getreserveday();
    };

    for (const auto &r : reservation)
    {
        if (!r.getMeal())
            continue;

        bool dupWithConfirmed = any_of(current.begin(), current.end(),
                                       [&](const Reservation &x)
                                       { return sameMealDay(x, r) && x.getstatus() == Confirmed; });

        bool dupInsideBatch = any_of(toConfirm.begin(), toConfirm.end(),
                                     [&](const Reservation &x)
                                     { return sameMealDay(x, r); });

        bool dupWithCancelled = any_of(current.begin(), current.end(),
                                       [&](const Reservation &x)
                                       { return sameMealDay(x, r) && x.getstatus() == Cancelled; });

        if (dupWithConfirmed || dupInsideBatch || dupWithCancelled)
        {
            cout << "You already tried reserving this meal for that day.\n";
            continue;
        }

        toConfirm.push_back(r);
        total += r.getMeal()->getprice();
    }

    if (toConfirm.empty())
    {
        cout << "Nothing to confirm.\n";
        reservation.clear();
        return;
    }

    if (student->getBalance() < total)
    {
        cout << "Not enough balance (" << student->getBalance()
             << " < " << total << "). Use option 8 to increase balance.\n";
        return;
    }

    float newBalance = student->getBalance();

    for (auto &r : toConfirm)
    {
        r.setStatus(Confirmed);
        r.setReservationID(time(nullptr));
        current.push_back(r);

        newBalance -= r.getMeal()->getprice();
    }

    student->setBalance(newBalance);
    student->setreservation(current);

    save_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");
    save_student_balance(*student, "students.json");

    reservation.clear();

    cout << "Reservations confirmed and saved.\n";
    cout << "Remaining balance: " << student->getBalance() << "\n";
}
inline bool ShoppingCart::addReservation(const Reservation &r, const Student *student)
{
    if (!r.getMeal())
    {
        cout << "Meal is invalid.\n";
        return false;
    }

    int mid = r.getMeal()->getmealid();
    auto mday = r.getMeal()->getreserveday();

    bool dupInCart = any_of(reservation.begin(), reservation.end(),
                            [mid, mday](const Reservation &x)
                            {
                                return x.getMeal() &&
                                       x.getMeal()->getmealid() == mid &&
                                       x.getMeal()->getreserveday() == mday;
                            });
    if (dupInCart)
    {
        cout << "This meal for that day is already in your cart.\n";
        return false;
    }

    if (student)
    {
        const auto &confirmed = student->getReserves();
        bool dupConfirmed = any_of(confirmed.begin(), confirmed.end(),
                                   [mid, mday](const Reservation &x)
                                   {
                                       return x.getMeal() &&
                                              x.getMeal()->getmealid() == mid &&
                                              x.getMeal()->getreserveday() == mday &&
                                              x.getstatus() != Cancelled;
                                   });
        if (dupConfirmed)
        {
            cout << "You already reserved this meal for that day.\n";
            return false;
        }
    }

    reservation.push_back(r);
    cout << "Reservation added to cart.\n";
    return true;
}
inline void ShoppingCart::removeFromCart(int reservationID)
{
    auto it = remove_if(reservation.begin(), reservation.end(),
                        [&](const Reservation &r)
                        { return r.getReservationId() == reservationID && r.getstatus() == Pending; });

    if (it != reservation.end())
    {
        reservation.erase(it, reservation.end());
        cout << "Reservation removed from cart.\n";
    }
    else
    {
        cout << "Reservation ID not found in cart.\n";
    }
}
inline void ShoppingCart::removeConfirmedReservation(int reservationID, Student *student, bool hardDelete)
{
    if (!student)
    {
        cout << "No student logged in.\n";
        return;
    }

    vector<Reservation> current = student->getReserves();
    vector<Reservation> updated;
    bool found = false;

    for (auto &r : current)
    {
        if (r.getReservationId() == reservationID && r.getstatus() == Confirmed)
        {
            found = true;
            if (r.getMeal())
            {
                int price = r.getMeal()->getprice();
                int penalty = (price * 20) / 100;
                int refund = price - penalty;

                student->setBalance(student->getBalance() + refund);

                cout << "Reservation cancelled. 20% penalty applied. Refund: " << refund << "\n";

                if (hardDelete)
                {
                    continue;
                }
                else
                {
                    r.setStatus(Cancelled);
                }
            }
        }
        updated.push_back(r);
    }

    if (found)
    {
        student->setreservation(updated);

        save_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");

        cout << "Reservation updated in file.\n";
    }
    else
    {
        cout << "Reservation ID not found.\n";
    }
}
inline bool ShoppingCart::removeReservation(Student *student, int reservationID)
{
    if (!student)
    {
        cout << " No student logged in.\n";
        return false;
    }

    vector<Reservation> current = student->getReserves();
    auto it = find_if(current.begin(), current.end(),
                      [&](const Reservation &r) { return r.getReservationId() == reservationID; });

    if (it != current.end())
    {
        if (it->getstatus() == Confirmed && it->getMeal())
        {
            float refund = it->getMeal()->getprice() * 0.8f; 
            student->setBalance(student->getBalance() + refund);
            cout << "Reservation removed. 20% penalty applied. Refund: " << refund << "\n";
        }
        else
        {
            cout << "Reservation removed from cart.\n";
        }

  
        current.erase(it);

        student->setreservation(current);
        save_student_reservations(*student, "reservations_" + student->getStudentId() + ".json");

        return true;
    }

    cout << "Reservation ID not found.\n";
    return false;
}