#include "includes/admin.hpp"
#include "includes/reservation.hpp"
//#include "includes/studentpanel.hpp"
#include "includes/student.hpp"
#include "includes/dininghall.hpp"
#include "includes/meal.hpp"
//#include "includes/user.hpp"
#include <fstream>


int main (){
    Student s;
s.setUserId(1234567890);
s.setName("Seyed");
s.setEmail("seyed@example.com");
s.setBalance(100000);
s.setIsActive(true);
s.setHasrRservation(false);


json j = s.to_json();
ofstream out("students.json");
out << j.dump(4);
out.close();


ifstream in("students.json");
json j2;
in >> j2;
Student loaded;
loaded.from_json(j2);
loaded.print();
    
}
