#pragma once
#include <iostream>
#include <vector>
#include "reservation.hpp"
#include "json.hpp"
using namespace std;
using json = nlohmann ::json;
class ShoppingCart
{
    vector<Reservation> reservation;

public:
    void addReservation(const Reservation &r)
    {
        reservation.push_back(r);
        cout << "reserve added to cart .\n";
    }
    void removeReservation(int ID)
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
    void clear()
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
        clear();
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
