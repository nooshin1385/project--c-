#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
class User
{
    int UserId;
    string Name;
    string LastName;
    string HashedPassword;

public:
    User(int _userid, string _name, string _lastname, string _hpassword) : UserId(_userid), Name(_name), LastName(_lastname), HashedPassword(_hpassword) {}
    virtual void print() const;
    virtual void getType()
    {
        cout << "this is user." << endl;
    }
    User() {}
};

class Student : public User
{
    int UserId;
    string StudentId;
    string Name;
    string Email;
    float Balance;
    bool IsActive;
    bool Hasreservation = false;     // there is any reserve or no ?
    vector<Reservation> reservation; // list for reserves
    int Phone;

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
        Phone = 0;
    }
    Student(int user_id, string student_id, string _name, string _email, float _balance, bool is_active = true, vector<Reservation> _reservation, int _phone)
    {
        try
        {
            setUserId(to_string(user_id));
            setStudentId(student_id);
            setEmail(_email);
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
        reservation = _reservation;
        Phone = _phone;
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
            Phone = ob.Phone;
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
    void setStudentId(string _studentID)
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
    void setName(string _name)
    {
        Name = _name;
    }
    void setEmail(string _email)
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
    void setBalance(float _balance)
    {
        Balance = _balance;
        if (Balance < 0)
        {
            cout << "you are in debt and you cannot reserve food";
        }
    }
    void setIsActive(bool status)
    {
        IsActive = status;
    }
    void setHasrRservation(bool reservationstatus)
    {
        Hasreservation = reservationstatus;
    }
    void setreservation(vector<Reservation> _reservation)
    {
        reservation = _reservation;
    }
    void setphone(int _phone)
    {
        Phone = _phone;
    }
    int getUserId() { return UserId; }
    string getStudentId() { return StudentId; }
    string getName() { return Name; }
    string getEmail() { return Email; }
    float getBalance() { return Balance; }
    bool getIsActive() { return IsActive; }
    bool getHasReservation() { return Hasreservation; }
    vector<Reservation> getreservatin() { return reservation; }
    int getphone() { return Phone; }
    void ReserveMeal()
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
    bool CancelReservation()
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
    void AddReservatin(const Reservation &reservation)
    {
    }
    void Activate()
    {
        IsActive = true;
        cout << "student account is active .\n";
    }
    void Deactivate()
    {
        IsActive = false;
        cout << "student account is deactive .\n";
    }
    bool Isactive()
    {
        return IsActive;
    }
    void Print() const
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
    void setsideitems(vector<string> _SideItems) { SideItems = _SideItems; }
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
class DiningHall
{
    int HallID;
    string Name;
    string Address;
    int Capacity;

public:
    DiningHall()
    {
        HallID = 0;
        Name = "";
        Address = "";
        Capacity = 0;
    }
    DiningHall(int _HallID, string _Name, string _Address, int _Capacity)
    {
        HallID = _HallID;
        Name = _Name;
        Address = _Address;
        Capacity = _Capacity;
    }
    void sethallid(int _hallID)
    {
        HallID = _hallID;
    }
    void setname(string _name)
    {
        Name = _name;
    }
    void setaddress(string _address)
    {
        Address = _address;
    }
    void setcapacity(int _capacity)
    {
        Capacity = _capacity;
    }
    int gethallid() { return HallID; }
    string getname() { return Name; }
    string getaddress() { return Address; }
    int getcapacity() { return Capacity; }

    void printdininghallinfo()
    {
        cout << "Dining hall info :" << endl;
        cout << "ID :" << HallID << endl;
        cout << "Name :" << Name << endl;
        cout << "Address :" << Address << endl;
        cout << "Capacity :" << Capacity << endl;
        cout << "----------------------" << endl;
    }
};