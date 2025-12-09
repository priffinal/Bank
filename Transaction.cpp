#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int Transaction::ID = 1;

Transaction::Transaction() {}
Transaction::~Transaction() {}

Transaction::Transaction(string aID, string date, long long amount, string type, string status)
{
    this->accountID = aID;
    this->dateTime = date;
    this->amount = amount;
    this->type = type;
    this->status = status;
}

void Transaction::generateID()
{
    stringstream s;
    if (type == "deposit") {
        s << "DP" << setw(4) << setfill('0') << ID++;
    } else if (type == "withdraw") {
        s << "WD" << setw(4) << setfill('0') << ID++;
    }
    transactionID = s.str();
}

void Transaction::log()
{
    generateID();
    cout << "ID giao dich: " << transactionID << endl;
    cout << "TK giao dich: " << accountID << endl;
    cout << "Loai giao dich: " << type << endl;
    cout << "Ngay giao dich: " << dateTime << endl; 
    cout << "So tien: " << amount << endl;
    cout << "Trang thai: " << status << endl;
}