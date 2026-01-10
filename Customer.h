#pragma once
#include <vector>
#include<string>
using namespace std;

class Account;

class Customer
{
private:
    string customerID;
    string fullName;
    string phone;
    string email;
    string address;
    vector<Account*> account;
   // static int n;
public:
    Customer();
    string addAccount(Account *acc);
    int getAccountCount();
    Account* searchAccount(string ID);
    string getID();
    string getName();
    string getPhone();
    string getAddress();
    string getEmail();
    void showInfo();
    void updateInfo(string name, string phone, string email, string address);
    bool removeAccount(string accID);
    void createCustomer(string name, string phone, string email, string address);
    void autoID(string ID);
    bool removeAllAccount();
    void list();
    long long totalBalance();
};