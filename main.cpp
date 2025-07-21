#include "includes/admin.hpp"
#include "includes/reservation.hpp"
#include "includes/studentpanel.hpp"
#include "includes/student.hpp"
#include "includes/dininghall.hpp"
#include "includes/meal.hpp"
#include "includes/user.hpp"
#include <fstream>
#include "includes/shoppingcart.hpp"
#include "includes/sessions.hpp"
#include "includes/adminpanel.hpp"
#include <iostream>

using namespace std;
int main()
{
    AdminPanel p;
    p.showMenu();
    return 0;
}
