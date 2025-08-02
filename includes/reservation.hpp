#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "student.hpp"
#include "meal.hpp"
#include "dininghall.hpp"

using namespace std;
enum Rstatus
{
    Confirmed,
    Cancelled,
    Pending
};
class Reservation
{
    int Reservation_ID;
    time_t Created_at;
    Rstatus status;
    Meal *meal;
    DiningHall *dHall;

public:
    Reservation(int _ReservationID, Rstatus intialstatus, Meal *_meal, DiningHall *_dHall)
    {

        Reservation_ID = _ReservationID;
        status = intialstatus;
        Created_at = time(nullptr);
        meal = _meal;
        dHall = _dHall;
    }
    Reservation()
    {
        Reservation_ID = 0;
        status = Pending;
    }
    void setReservationID(int _ID)
    {
        Reservation_ID = _ID;
    }

    void setStatus(Rstatus _status)
    {
        status = _status;
    }
    void setTime(time_t _createdat)
    {
        Created_at = _createdat;
    }
    void setMeal(Meal *_meal)
    {
        meal = _meal;
    }
    void setDininghall(DiningHall *_dHall)
    {
        dHall = _dHall;
    }
    int getReservationId() const { return Reservation_ID; }
    Rstatus getstatus() const { return status; }
    time_t gettime() const { return Created_at; }
    Meal *getMeal() const { return meal; }
    DiningHall *getdHall() const { return dHall; }
    bool CancelReservation()
    {
        if (status == Confirmed || status == Pending)
        {
            status = Cancelled;
            return true;
        }
        else
        {
            return false;
        }
    }
    void printReservationinfo() const
    {
        cout << "Reservation ID :" << Reservation_ID << endl;
        if (meal)
        {
            cout << "Meal:" << meal->getmealname() << endl;
        }
        if (dHall)
        {
            cout << "Dining hall :" << dHall->getname() << endl;
        }
        cout << "Status :";
        switch (status)
        {
        case Pending:
            cout << "Pending ";
            break;
        case Confirmed:
            cout << "Confirmed";
            break;
        case Cancelled:
            cout << "Cancelled";
            break;
        }
        cout << "Created at :" << ctime(&Created_at) << endl;
    }
    json to_json() const
    {
        return {
            {"Reservation_ID", Reservation_ID},
            {"Created_at", Created_at},
            {"status", status},
            {"Meal", meal->to_json()},
            {"Dininghall", dHall->to_json()}};
    }
    void from_json(const json &j)
    {
        Reservation_ID = j.at("Reservation_ID").get<int>();
        Created_at = j.at("Created_at").get<time_t>();
        status = j.at("status").get<Rstatus>();
        meal = new Meal() ;
        meal->from_json(j.at("Meal"));
        dHall=new DiningHall();
        dHall->from_json(j.at("Dininghall"));
    }
    NLOHMANN_JSON_SERIALIZE_ENUM(Rstatus, {{Pending, "Pending"},
                                           {Confirmed, "Confirmed"},
                                           {Cancelled, "Cancelled"}})

                                           
};
inline void to_json(json &j, const Reservation &r)
{
    j = r.to_json();
}

inline void from_json(const json &j, Reservation &r)
{
    r.from_json(j);
}