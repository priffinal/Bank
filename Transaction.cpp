#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

map<string, int> Transaction::counter = {};

Transaction::Transaction() {}
Transaction::~Transaction() {}

ostream& operator<<(ostream &os, tm *ltm)
{
    os << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec
    << " " << (ltm->tm_mday < 10 ? "0":"") << ltm->tm_mday << "/"
    << (ltm->tm_mon + 1 < 10 ? "0":"") << ltm->tm_mon + 1 << "/"
    << ltm->tm_year + 1900;
    return os;
}

Transaction::Transaction(string aID, string rID, tm *date, long long amount, string type, string status)
{
    this->accountID = aID;
    this->relatedID = rID;
    this->dateTime = date;
    this->amount = amount;
    this->type = type;
    this->status = status;
}

void Transaction::generateID()
{
    stringstream s;
    if (type == "deposit") {
        counter["deposit"]++;
        s << "DEP" << setw(4) << setfill('0') << counter["deposit"];
    } else if (type == "withdraw") {
        counter["withdraw"]++;
        s << "WDR" << setw(4) << setfill('0') << counter["withdraw"]++;
    } else if (type == "transfer_in") {
        counter["transfer_in"]++;
        s << "TFI" << setw(4) << setfill('0') << counter["transfer_in"]++;
    } else if (type == "transfer_out") {
        counter["transfer_out"]++;
        s << "TFO" << setw(4) << setfill('0') << counter["transfer_out"]++;
    }

    transactionID = s.str();
}

void Transaction::log()
{
    generateID();
    cout << "ID giao dich: " << transactionID << endl;
    cout << "TK giao dich: " << accountID << endl;
    if (type == "transfer") {
        cout << "TK nhan tien: " << relatedID << endl;
    }
    cout << "Loai giao dich: " << type << endl;
    cout << "Ngay giao dich: " << dateTime << endl; 
    cout << "So tien: " << amount << endl;
    cout << "Trang thai: " << status << endl;
}