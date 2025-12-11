#pragma once
#include"Account.h"
#include <vector>
#include<string>
using namespace std;
class Account;
class Customer
{
    string customerID;
    string fullName;
    string phone;
    string email;
    string address;
    vector<Account*> account;
    static int n;
public:
    Customer();
    void addAccount();
    string getID();
    void showinfo();
    void updateInfo();
    bool removeAccount(string accID);

    double getBalance();
    void createCustomer();

};