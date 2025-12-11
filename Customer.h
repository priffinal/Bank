#pragma once
#include"Account.h"
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
    Account* account[1000];
    int n = 0;

public:
    Customer();
    void addaccount();
    string getID();
    void showinfo();
    void updateInfo(string name, string p, string e, string addr);
    bool removeAccount(string accID);

    double getBalance();
    void createcustomer();

};