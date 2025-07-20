#include "includes/admin.hpp"
#include "includes/reservation.hpp"
#include "includes/studentpanel.hpp"
#include "includes/student.hpp"
#include "includes/dininghall.hpp"
#include "includes/meal.hpp"
#include "includes/user.hpp"
#include <fstream>
#include "includes/shoppingcart.hpp"
#include <iostream>
//#include "json.hpp"
using namespace std;
//using json = nlohmann :: json ;


int main() {
    cout << "🎓 Welcome to Student Food Reservation System 🎓\n";

    StudentPanel panel;
    panel.showMenu(); 

    cout << "\n🛑 Application exited. Goodbye!\n";
    return 0;
}


