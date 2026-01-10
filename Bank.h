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
    int extractNumber(const string& ID);
public:
    Bank();
    ~Bank();

    // Quan ly khach hang
    string addCustomer(string name, string phone, string email, string address, string ID);
    Customer* searchCustomer(const string &ID);
    bool updateCusInfo(string ID, string name, string phone, string email, string address);
    bool showCusInfo(string ID);
    bool deleteCustomer(string ID);
    void customerStatistics(int &totalCus, int &noAcc, string &mostAccCusID, string &richestCusID, long long &maxTotalBalance);
    
    // Quan ly tai khoan
    string addCHK(string ID, long long balance, long long overdraftLimit, tm date, string status);
    string addSAV(string ID, long long balance, int term, float interestRate, tm date, string status);
    bool showAccInfo(string ID);
    void closeAccount(string accID);
    Account* searchAccount(const string &ID);
    void deposit(Account &a, double amount);
    bool withdraw(Account &a, double amount);
    bool transfer(Account &a, string ID, double amount);
    void accountStatistics(int &totalAcc, int &checkingCnt, int &savingCnt, int &overdraftCnt,
                           long long &totalBalance, long long &maxBalance, string &maxBalAccID);
    
    // Quan ly giao dich
    void printAllTransactions();
    void countTransactions(int &n1, int &n2, int &n3);
    void successRate(int &n1, int &n2);

    // Loc giao dich
    vector<Transaction> filterByDate(tm from, tm to);
    vector<Transaction> filterByID(string ID);
    vector<Transaction> filterByType(string type);
    vector<Transaction> sortTransaction(int type);

    // Doc, in ra file
    void loadCusFromFile(const string& filename);
    void saveCusToFile(const string& filename);
    void loadAccFromFile(const string& filename);
    void saveAccToFile(const string& filename);
    void loadTransFromFile(const string& filename);
    void saveTransToFile(const string& filename);

    // loc custmoer, account, transaction
    void filterCustomer();
    void filterAccountByBalance();
    void filterTransactionByType();
    void filterAccountByID();
    void filterAccountByDate(tm from, tm to);

    // sap xep
    void sortCustomer();
    void sortAccountBybalance();
    void sortAccountByID();
    void sortAccountByDate();
};