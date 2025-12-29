#pragma once
#include "Customer.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include"menu.h"
#include <vector>
#include <map>
using namespace std;

class Bank
{
private:
    vector<Customer> customers;
    vector<Account*> accounts;
    vector<Transaction> transactions;
    static int cusNum, accNum;
    menu ui;
public:
    Bank();
    ~Bank();
    void addCustomer();
    void showCusInfo(string ID);
    void updateCusInfo(string ID);
    void deleteCustomer(string ID);
    void addAccount();
    void closeAccount();
    Customer* searchCustomer(string ID);
    Account &searchAccount(string ID);
    void deposit(Account &a, double amount);
    void withdraw(Account &a, double amount);
    void transfer(Account &a, string ID, double amount);
    void list();
    void run();
    void accountmenu();
    void customermenu();
    void transactionmenu();
};