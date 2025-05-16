#include <iostream>
#include <vector>
#include "reservation.hpp"
using namespace std;
class ShoppingCart
{
    vector<Reservation> reservation;

public:
    // Transaction confirm();
    void addReservation(Reservation const &r)
    {
        reservation.push_back(r);
        cout << "reserve added to cart ." << endl;
    }
    void removeReservation(int ID)
    {
        vector<Reservation> temp;
        for (size_t i = 0; i < reservation.size(); i++)
        {
            if (reservation[i].getReservationId() == ID)
            {
                i++;
            }
            temp.push_back(reservation[i]);
        }
        reservation = temp;
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
            for (Reservation &r : reservation)
            {
                r.printReservationinfo();
            }
        }
    }
    void clear()
    {
        reservation.clear();
        cout << "Shopping cart si clear now.\n";
    }
    const vector<Reservation> &getreservation() const
    {
        return reservation;
    }
};
