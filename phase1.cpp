#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

class Student
{
    int UserId;
    string StudentId;
    string Name;
    string Email;
    float Balance;
    bool IsActive;
    bool Hasreservation = true; // there is any reserve or no ?

public:
    Student()
    {
        UserId = 0;
        StudentId = "0000000000";
        Name = "ABC";
        Email = "abc@gmail.com";
        Balance = 0.0;
        IsActive = true;
        Hasreservation = true;
    }
    Student(int user_id, string student_id, string _name, string _email, float _balance, bool is_active = true)
    {
        try
        {
            setUserId(to_string(user_id));
            setstudentid(student_id);
            setemail(_email);
        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }

        StudentId = student_id;
        Name = _name;
        Email = _email;
        Balance = _balance;
        IsActive = is_active;
    }
    Student &operator=(Student &ob)
    {
        if (this != &ob)
        {
            UserId = ob.UserId;
            StudentId = ob.StudentId;
            Name = ob.Name;
            Email = ob.Email;
            Balance = ob.Balance;
            IsActive = ob.IsActive;
            Hasreservation = ob.Hasreservation;
        }
        return *this;
    }

    void setUserId(string _userID)
    {
        int count = 0;
        for (char c : _userID)
        {
            if (!isdigit(c))
            {
                throw "UserID must be just digits.";
            }
            count++;
        }

        if (count != 10)
        {
            throw "UserID must be exactly 10 digits.";
        }

        UserId = stoi(_userID);
    }
    void setstudentid(string _studentID)
    {
        int count = 0;
        for (char c : _studentID)
        {
            if (!isdigit(c))
            {
                throw "studentID must be just digits.";
            }
            count++;
        }
        if (count != 10)
            throw "studentID must be exactly 10 digits.";
        StudentId = _studentID;
    }
    void setname(string _name)
    {
        Name = _name;
    }
    void setemail(string _email)
    {
        int i = _email.find('@');
        if (i == -1)
        {
            throw "your email address should have @ !";
        }
        int j = _email.find('.', i);
        if (j == -1)
        {
            throw "your email address should have . !";
        }
        Email = _email;
    }
    void setbalance(float _balance)
    {
        Balance = _balance;
        if (Balance < 0)
        {
            cout << "you are in debt and you cannot reserve food";
        }
    }
    void setisactive(bool status)
    {
        IsActive = status;
    }
    void sethasreservation(bool reservationstatus)
    {
        Hasreservation = reservationstatus;
    }
    int getuserid() { return UserId; }
    string getstudentid() { return StudentId; }
    string getName() { return Name; }
    string getemail() { return Email; }
    float getbalance() { return Balance; }
    bool getisactive() { return IsActive; }
    bool gethasreservation() { return Hasreservation; }
    void reservemeal()
    {
        if (!IsActive)
        {
            cout << "you cannot reserve food because your account not active !" << endl;
        }
        else if (Balance < 0)
        {
            cout << "you are in debt and you can not reserve meal !" << endl;
        }
        else if (Hasreservation)
        {
            cout << "you already has a reservation !" << endl;
        }
        else
        {
            Hasreservation = true;
            cout << "your meal reserved successfully ." << endl;
        }
    }
    bool cancelreservation()
    {
        if (!Hasreservation)
        {
            cout << "you do not have any reserve !" << endl;
            return false;
        }
        else
        {
            Hasreservation = false;
            cout << "your reserve has cancelled" << endl;
            return true;
        }
    }
    void print()
    {
        cout << "student information :" << endl;
        cout << "User ID :" << UserId << endl;
        cout << "Student ID :" << StudentId << endl;
        cout << "Name :" << Name << endl;
        cout << "Email :" << Email << endl;
        cout << "Balance :" << Balance << endl;
        cout << "Active :" << (IsActive ? "yes" : "no") << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
};
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

public:
    Reservation(int _ReservationID, Student &S, Status intialstatus)
    {

        Reservation_ID = _ReservationID;
        S = student;
        status = intialstatus;
        Created_at = time(nullptr);
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
    int getReservationid() const { return Reservation_ID; }
    const Student &getStudent() const { return student; }
    Status getStatus() const { return status; }
    time_t gettime() const { return Created_at; }
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
        cout << "Student ID :" << student.getstudentid() << endl;
        cout << "Student Name :" << student.getName() << endl;
        cout << "Status :" << getStatus() << endl;
        cout << "Created at :" << ctime(&Created_at) << endl;
    }
};
enum MealType
{
    Appetizer,
    Mainmeal,
    Dessert,
    Beverage

};
class Meal
{
    int MealID;
    string MealName;
    float Price;
    MealType Type;
    vector<string> SideItems;

public:
    Meal()
    {
        MealID = 0;
        MealName = "";
        Price = 0.0;
        Type = Mainmeal;
    }
    Meal(int _mealid, string _mealname, float _price, MealType _type, vector<string> _sideitems)
    {
        MealID = _mealid;
        MealName = _mealname;
        Price = _price;
        Type = _type;
        SideItems = _sideitems;
    }
    void setmealid(int _MealID) { MealID = _MealID; }
    void setmealname(string _MealName) { MealName = _MealName; }
    void setprice(float _Price) { Price = _Price; }
    void settype(MealType _Type) { Type = _Type; }
    void setsudeitems(vector<string> _SideItems) { SideItems = _SideItems; }
    int getmealid() { return MealID; }
    string getmealname() { return MealName; }
    float getprice() { return Price; }
    MealType gettype() { return Type; }
    vector<string> getsideitems() { return SideItems; }
    void UpdatPrice(float new_price)
    {
        Price = new_price;
        cout << "new price of" << MealName << "is" << Price << "." << endl;
    }
    void Addsideitem(string item)
    {
        SideItems.push_back(item);
        cout << item << "Added to" << MealName << "as an item ." << endl;
    }
    void printmealinfo()
    {
        cout << "Meal ID:" << MealID << endl;
        cout << "Meal Name :" << MealName << endl;
        cout << "Price :" << Price << endl;
        cout << "Type :";
        switch (Type)
        {
        case Appetizer:
            cout << "Appetizer";
            break;
        case Mainmeal:
            cout << "MainMeal";
            break;
        case Dessert:
            cout << "Dessert";
            break;
        case Beverage:
            cout << "Beverage";
            break;
        }
        cout << endl;
        cout << "SideItems :";
        for (int i = 0; i < SideItems.size(); i++)
        {
            cout << SideItems[i] << " ";
        }
        cout << endl;
    }
};