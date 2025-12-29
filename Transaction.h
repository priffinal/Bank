#pragma once
#include <map>
#include <ctime>
#include <string>
using namespace std;

class Transaction
{
private:
    static map<string, int> counter;
    string transactionID;
    string accountID;
    string relatedID;
    tm dateTime;
    long long amount;
    string type;
    string status;
public:
    Transaction();
    Transaction(string aID, string rID, tm date, long long amount, string type, string status);
    ~Transaction();
    string getType();
    string getAccID();
    long long getAmount();
    tm getTime();
    void generateID();
    void log();
};