#include <iostream>
#include <string>
#include "Bank.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include "Account.h"
#include"Customer.h"
#include "Menu.h"
using namespace std;

int main() {
	Bank b;
    Menu menu = Menu(b);
    menu.mainMenu();
}