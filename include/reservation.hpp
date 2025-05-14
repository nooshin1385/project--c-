#include <iostream>
#include <ctime>
#include <vector>
#include "student.hpp"
#include "meal.hpp"
#include "dininghall.hpp"
using namespace std ;
enum Status
{
    Confirmed,
    Cancelled,
    Pending
};
class Reservation
{
    Student student;
    int Reservation_ID;
    time_t Created_at;
    Status status;
    Meal meal;
    DiningHall dHall;

public:
    Reservation(int _ReservationID, Student &S, Status intialstatus, Meal _meal, DiningHall _dHall)
    {

        Reservation_ID = _ReservationID;
        S = student;
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
    void setStudent(Student _student)
    {
        student = _student;
    }
    void setStatus(Status _status)
    {
        status = _status;
    }
    void setTime(time_t _createdat)
    {
        Created_at = _createdat;
    }
    void setMeal(Meal _meal)
    {
        meal = _meal;
    }
    void setDininghall(DiningHall _dHall)
    {
        dHall = _dHall;
    }
    int getReservationid() const { return Reservation_ID; }
    Student getStudent() const { return student; }
    Status getStatus() const { return status; }
    time_t gettime() const { return Created_at; }
    Meal getMeal() const { return meal; }
    DiningHall getdHall() const { return dHall; }
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
    void printReservationinfo()
    {
        cout << "Reservation ID :" << Reservation_ID << endl;
        cout << "Student ID :" << student.getStudentId() << endl;
        cout << "Student Name :" << student.getName() << endl;
        cout << "Status :" << getStatus() << endl;
        cout << "Created at :" << ctime(&Created_at) << endl;
    }
};
enum Reserveday
{
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday

};