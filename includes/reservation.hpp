#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "student.hpp"
#include "meal.hpp"
#include "dininghall.hpp"

using namespace std;
class Student;
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
    Student *student;

public:
    Reservation(int _ReservationID, Rstatus intialstatus, Meal *_meal, DiningHall *_dHall, Student *_student)
    {

        Reservation_ID = _ReservationID;
        status = intialstatus;
        Created_at = time(nullptr);
        meal = _meal;
        dHall = _dHall;
        student = _student;
    }
    ~Reservation()
    {
       // delete meal;
        //delete dHall;
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
        json j;
        j["Reservation_ID"] = Reservation_ID;
        j["Created_at"] = Created_at;
        j["status"] = static_cast<int>(status);

        if (meal)
            j["Meal"] = meal->to_json();
        else
            j["Meal"] = nullptr;

        if (dHall)
            j["Dininghall"] = dHall->to_json();
        else
            j["Dininghall"] = nullptr;

        return j;
    }
    void from_json(const json &j)
    {
        Reservation_ID = j.at("Reservation_ID").get<int>();
        Created_at = j.at("Created_at").get<time_t>();
        status = static_cast<Rstatus>(j.at("status").get<int>());

        if (j.contains("Meal") && !j["Meal"].is_null())
        {
            meal = new Meal();
            meal->from_json(j["Meal"]);
        }
        else
        {
            meal = nullptr;
        }

        if (j.contains("Dininghall") && !j["Dininghall"].is_null())
        {
            dHall = new DiningHall();
            dHall->from_json(j["Dininghall"]);
        }
        else
        {
            dHall = nullptr;
        }
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