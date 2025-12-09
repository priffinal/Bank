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

string Transaction::generateID()
{
    stringstream s;
    if (status == "deposit") {
        s << "DP" << setw(4) << setfill('0') << ID++;
    } if (status == "withdraw") {
        s << "WD" << setw(4) << setfill('0') << ID++;
    }
    transactionID = s.str();
    return transactionID;
}

void Transaction::log()
{
    cout << "ID giao dich: " << generateID() << endl;
    cout << "Loai giao dich: " << type << endl;
    cout << "Ngay giao dich: " << dateTime << endl; 
    cout << "TK giao dich: " << accountID << endl;
    cout << "So tien: " << amount << endl;
    cout << "Trang thai: " << status << endl;
}