#pragma once
#include "Customer.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
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
public:
    Bank();
    ~Bank();
    string addCustomer(string name, string phone, string email, string address);
    bool showCusInfo(string ID);
    bool showAccInfo(string ID);
    bool updateCusInfo(string ID, string name, string phone, string email, string address);
    bool deleteCustomer(string ID);
    string addCHK(string ID, long long balance, long long overdraftLimit);
    string addSAV(string ID, long long balance);
    void closeAccount(string accID);
    Customer* searchCustomer(const string &ID);
    Account* searchAccount(const string &ID);
    void deposit(Account &a, double amount);
    bool withdraw(Account &a, double amount);
    bool transfer(Account &a, string ID, double amount);
    void printAllTransactions();
    long long totalDeposit();
    long long totalWithdraw(string ID);
    vector<Transaction> filterByDate(tm from, tm to);
};