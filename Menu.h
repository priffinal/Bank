#pragma once
#include "Bank.h"

class Menu
{
private:
    Bank &bank;
    void customerMenu();
    void accountMenu();
    void transactionMenu();
    void firstRow();

    void addCustomer();
    string checkCustomer();
    void editCusInfo();
    void showCusInfo();
    void deleteCustomer();

    string checkAccount();
    void openAccount();
    void closeAccount();
    void showAccInfo();
    void deposit();
    void withdraw();
    void transfer();

    void filterByAccount();
    void filterByType();
    void filterByDate();

public:
    ~Menu();
    Menu (Bank &b);
    void mainMenu();
};