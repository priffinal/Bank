#include <iostream>
#include "Bank.h"
#include "Menu.h"
using namespace std;

int main() {
	Bank b;
    b.loadCusFromFile("customers.txt");
    b.loadAccFromFile("accounts.txt");
    b.loadTransFromFile("transactions.txt");

    Menu menu = Menu(b);
    menu.mainMenu();

}