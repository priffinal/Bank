#pragma once
#include "Customer.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include <vector>
using namespace std;

class Bank
{
private:
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;
public:
    Bank();
    ~Bank();
    void addCustomer();
    void showCusInfo();
    void updateCusInfo();
    void deleteCus();
    void addAccount();
    void closeAccount();
    void searchCustomer();
    void searchAccount();
    void deposit(Account a);
    void withdraw(Account a);
    void transfer(Account a, Account b);
    void list();
};