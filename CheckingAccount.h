#pragma once
#include "Account.h"
using namespace std;
class CheckingAccount : public Account
{
private:
    double overdraftLimit; // Gioi han thau chi

public:
    CheckingAccount(string id, string name, double initialBalance, double limit);

    double calculateInterest() override;
    bool withdraw(double amount) override;
};