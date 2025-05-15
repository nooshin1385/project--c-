#include <iostream>
using namespace std;
class Panel
{

public:
    Panel() {}
    void Action(int);
    void showMenu();
    void exit();



    
    void showStudentInfo();

    void checkBalance();

    void viewReservations();

    void addReservation(Reservation);

    void addToShoppingCart();

    void confirmShoppingCart();

    void removeShoppingCartItem();

    void increaseBalance();

    void viewRecentTransactions();

    void cancelReservation(int);

};