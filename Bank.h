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
    bool showCusInfo(string ID);
    bool showAccInfo(string ID);
    bool updateCusInfo(string ID, string name, string phone, string email, string address);
    bool deleteCustomer(string ID);
    bool withdraw(Account &a, double amount);
    bool transfer(Account &a, string ID, double amount);
    long long totalDeposit();
    long long totalWithdraw(string ID);
    void deposit(Account &a, double amount);
    void printAllTransactions();
    void printTransaction();
    void closeAccount(string accID);
    string addCustomer(string name, string phone, string email, string address);
    string addCHK(string ID, long long balance, long long overdraftLimit);
    string addSAV(string ID, long long balance);
    Account* searchAccount(const string &ID);
    Customer* searchCustomer(const string &ID);
    vector<Transaction> filterByDate(tm from, tm to);
    vector<Transaction> filterByID(string ID);
    vector<Transaction> filterByType(string type);
};