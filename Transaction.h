#pragma once
#include <map>
#include <ctime>
#include <string>
using namespace std;

class Transaction
{
private:
    static map<string, int> counter;
    friend ostream& operator<<(ostream &os, tm *ltm);
    string transactionID;
    string accountID;
    string relatedID;
    tm *dateTime;
    long long amount;
    string type;
    string status;
public:
    Transaction();
    Transaction(string aID, string rID, tm *date, long long amount, string type, string status);
    ~Transaction();
    void generateID();
    void log();
};