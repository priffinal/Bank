#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

map<string, int> Transaction::counter = {};

Transaction::Transaction() {}
Transaction::~Transaction() {}

Transaction::Transaction(string aID, string rID, tm date, long long amount, string type, string status)
{
    this->accountID = aID;
    this->relatedID = rID;
    this->dateTime = date;
    this->amount = amount;
    this->type = type;
    this->status = status;
    generateID();
}

Transaction::Transaction(string transID, string aID, string rID, tm date, long long amount, string type, string status)
{
    this->transactionID = transID;
    this->accountID = aID;
    this->relatedID = rID;
    this->dateTime = date;
    this->amount = amount;
    this->type = type;
    this->status = status;

}

void Transaction::generateID()
{
    if (type == "deposit") {
        transactionID = autoGenerate("DEP", ++counter["deposit"]);
    } else if (type == "withdraw") {
        transactionID = autoGenerate("WDR", ++counter["withdraw"]);
    } else if (type == "transfer_in") {
        transactionID = autoGenerate("TFI", ++counter["transfer_in"]);
    } else if (type == "transfer_out") {
        transactionID = autoGenerate("TFO", ++counter["transfer_out"]);
    }
}

void Transaction::log()
{
    auto formatAmount = [](long long v) {
        bool neg = v < 0;
        unsigned long long n = neg ? (unsigned long long)(-v) : (unsigned long long)v;
        string s = to_string(n);
        for (int i = (int)s.length() - 3; i > 0; i -= 3) s.insert(i, ",");
        if (neg) s.insert(0, "-");
        return s;
    };

    string amt = formatAmount(amount);

    cout << left
         << setw(12) << transactionID
         << setw(15) << accountID
         << setw(15) << (relatedID.empty() ? "------" : relatedID)
         << setw(25) << dateTime
         << setw(15) << amt
         << setw(20) << type
         << setw(15) << status
         << endl;
}

string Transaction::getType() { return type; }

long long Transaction::getAmount() { return amount; }

string Transaction::getAccID() { return accountID; }

tm Transaction::getTime() { return dateTime; }

string Transaction::getStatus() { return status; }

string Transaction::toFileString() const {
    ostringstream oss;
    oss << type << "|"
        << transactionID << "|"
        << accountID << "|"
        << (relatedID.empty() ? "------" : relatedID) << "|"
        << dateTime << "|"
        << amount << "|"
        << status;
    return oss.str();
}

Transaction Transaction::fromFileString(const string& line) {
    string type, id, from, to, timeStr, status;
    long long amount;

    stringstream ss(line);
    getline(ss, type, '|');
    getline(ss, id, '|');
    getline(ss, from, '|');
    getline(ss, to, '|');
    getline(ss, timeStr, '|');
    ss >> amount;
    ss.ignore();
    getline(ss, status);

    tm t = {};
    istringstream iss(timeStr);
    iss >> get_time(&t, "%H:%M:%S %d/%m/%Y");

    if (to == "------") to = "";

    return Transaction(id, from, to, t, amount, type, status);
}

void Transaction::updateCounter(string type, int val) {
    if (val > counter[type]) {
        counter[type] = val;
    }
}