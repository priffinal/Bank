#pragma once
// #include"Account.h"
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
    static int n;
public:
    Customer();
    Account* addAccount();
    int getAccountCount();
    Account* getAccountAt(int index);
    string getID();
    void showInfo();
    void updateInfo();
    bool removeAccount(string accID);
    void createCustomer();
    void autoID(string ID);
};