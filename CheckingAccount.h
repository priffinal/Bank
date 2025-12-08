#pragma once
#include "Account.h"
using namespace std;
class CheckingAccount : public Account
{
private:
    double transactionFee; // Phi giao dich
    double overdraftLimit; // Gioi han thau chi (so tien duoc no)

public:
    
    CheckingAccount(string id, string name, double initialBalance, double fee, double limit);

    double calculateInterest() override; // Override phai cung kieu tra ve (double)
    bool withdraw(double amount) override; // Override ham rut tien
};