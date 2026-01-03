#pragma once
#include <vector>
#include <map>
#include <string>
using namespace std;

class Account;
class Customer;
class Transaction;

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

    Account* searchAccount(const string &ID);
    Customer* searchCustomer(const string &ID);

    bool showCusInfo(string ID);
    bool showAccInfo(string ID);
    bool updateCusInfo(string ID, string name, string phone, string email, string address);
    bool deleteCustomer(string ID);
    void deposit(Account &a, double amount);
    bool withdraw(Account &a, double amount);
    bool transfer(Account &a, string ID, double amount);

    void printAllTransactions();
    void closeAccount(string accID);
    string addCustomer(string name, string phone, string email, string address);
    string addCHK(string ID, long long balance, long long overdraftLimit);
    string addSAV(string ID, long long balance);
    void customerStatistics(int &totalCus, int &noAcc, string &mostAccCusID, string &richestCusID, long long &maxTotalBalance);
    void accountStatistics(int &totalAcc, int &checkingCnt, int &savingCnt, int &overdraftCnt,
                           long long &totalBalance, long long &maxBalance, string &maxBalAccID);
    void countTransactions(int &n1, int &n2, int &n3);
    void successRate(int &n1, int &n2);

    vector<Transaction> filterByDate(tm from, tm to);
    vector<Transaction> filterByID(string ID);
    vector<Transaction> filterByType(string type);
    vector<Transaction> sortTransaction(int type);
};