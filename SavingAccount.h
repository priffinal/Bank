#pragma once
#include "Account.h"
using namespace std;
class SavingAccount : public Account
{
private:
    double interestRate;   // Lai suat (%)
    double minimumBalance; // So du toi thieu de huong lai
    int term;              // Ky han (thang)

public:
    SavingAccount(string id, string name, double initialBalance, double rate, int termVal);

    double calculateInterest() override; // Sua kieu tra ve thanh double
    void applyInterest(); // Ham moi de cong lai vao goc
    void displayInfo() override;
};