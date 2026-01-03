#pragma once

class Bank;

class Menu
{
private:
    Bank &bank;
    void customerMenu();
    void accountMenu();
    void transactionMenu();
public:
    ~Menu();
    Menu (Bank &b);
    void mainMenu();
};