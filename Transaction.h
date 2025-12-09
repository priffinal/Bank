#pragma once
#include <string>
using namespace std;

class Transaction
{
private:
    string transactionID;
    string accountID;
    string dateTime;
    long long amount;
    string type;
    string status;
    static int ID;
public:
    Transaction();
    Transaction(string aID, string date, long long amount, string type, string status);
    ~Transaction();
    string generateID();
    void log();
};