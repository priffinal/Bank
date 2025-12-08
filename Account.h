#pragma once
#include <string>
#include <iostream>
using namespace std;

class Account
{
protected:
    std::string accountID;   // ID tai khoan
    std::string customerID;  // Ten chu tai khoan
    std::string openDate;    // Ngay tao tai khoan
    std::string status;      // Trang thai
    double balance;          // So du (Dung double cho tien te co phan thap phan)

public:
    Account(string id, string name, double initialBalance, string date = "01/01/2025");
    virtual ~Account();

    virtual bool withdraw(double amount);      // Rut tien
    virtual void deposit(double amount);       // Gui tien
    virtual double calculateInterest();        // Tinh lai suat
    virtual void displayInfo();                // Hien thi thong tin
    virtual double getBalance() const;         // Lay so du
    virtual void closeAccount();               // Dong tai khoan
};