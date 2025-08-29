#include <iostream>
#include <string>
#include "student.hpp"
#include "reservation.hpp"
#include <fstream>
using namespace std;
using json = nlohmann::json;

void save_student_reservations(const Student &student, const std::string &filename)
{
    json j;

    const auto &reservations = student.getReserves();

    for (const auto &r : reservations)
    {
        json item;

        item["Reservation_ID"] = r.getReservationId();
        item["Created_at"] = r.gettime();
        item["StudentId"] = student.getStudentId();

        if (r.getdHall())
            item["Dininghall"] = r.getdHall()->getname();
        else
            item["Dininghall"] = nullptr;

        if (r.getMeal())
        {
            json meal;
            Meal *m = r.getMeal();
            meal["MealID"] = m->getmealid();
            meal["MealName"] = m->getmealname();
            meal["Price"] = m->getprice();
            meal["IsActive"] = m->getisactive();
            meal["SideItems"] = m->getsideitems();
            meal["mealtype"] = m->gettype();
            meal["reserveday"] = m->getreserveday();
            item["Meal"] = meal;
        }
        else
        {
            item["Meal"] = nullptr;
        }

        item["status"] = static_cast<int>(r.getstatus());
        j.push_back(item);
    }

    std::ofstream out(filename);
    if (out.is_open())
    {
        out << j.dump(4);
        out.close();
    }
}
void load_student_reservations(Student &student, const std::string &filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
        return;

    json j;
    try
    {
        in >> j;
    }
    catch (const json::parse_error &e)
    {
        std::cout << "Error reading reservations file: " << e.what() << "\n";
        return;
    }
    in.close();
    for (const auto &item : j)
    {
        Reservation r;

        if (item.contains("Reservation_ID"))
            r.setReservationID(item["Reservation_ID"].get<long>());
        if (item.contains("Created_at"))
            r.setTime(item["Created_at"].get<time_t>());

        if (item.contains("Dininghall") && !item["Dininghall"].is_null())
        {
            DiningHall dh;
            dh.setname(item["Dininghall"].get<std::string>());
            r.setDininghall(&dh);
        }

        if (item.contains("Meal") && !item["Meal"].is_null())
        {
            Meal m;
            const auto &meal = item["Meal"];
            if (meal.contains("MealID"))
                m.setmealid(meal["MealID"].get<int>());
            if (meal.contains("MealName"))
                m.setmealname(meal["MealName"].get<std::string>());
            if (meal.contains("Price"))
                m.setprice(meal["Price"].get<float>());
            if (meal.contains("SideItems"))
                m.setsideitems(meal["SideItems"].get<std::vector<std::string>>());
            if (meal.contains("IsActive"))
                m.setisactive(meal["IsActive"].get<bool>());
            if (meal.contains("mealtype"))
                m.settype(static_cast<MealType>(meal["mealtype"].get<int>()));

            if (meal.contains("reserveday"))
                m.setreserveday(static_cast<Reserveday>(meal["reserveday"].get<int>()));
            r.setMeal(&m);
        }

        if (item.contains("status"))
            r.setStatus(static_cast<Rstatus>(item["status"].get<int>()));
        student.AddReservation(r);
    }
}
bool load_student_balance(Student &student, const std::string &path)
{
    std::ifstream in(path);
    if (!in.is_open())
        return false;

    json j;
    in >> j;
    in.close();

    for (auto &item : j)
    {
        if (item["StudentId"] == student.getStudentId())
        {
            student.setBalance(item["Balance"].get<double>());
            return true;
        }
    }
    student.setBalance(0);
    return false;
}
void save_student_balance(const Student &student, const std::string &path)
{
    std::ifstream in(path);
    json j;
    if (in.is_open())
    {
        in >> j;
        in.close();
    }

    bool found = false;
    for (auto &item : j)
    {
        if (item["StudentId"] == student.getStudentId())
        {
            item["Balance"] = student.getBalance();
            found = true;
            break;
        }
    }

    if (!found)
    {
        j.push_back({{"StudentId", student.getStudentId()},
                     {"Balance", student.getBalance()}});
    }

    std::ofstream out(path);
    out << j.dump(4);
    out.close();
}

double getDisplayBalance(const Student &student)
{
    return 0.0;
}
