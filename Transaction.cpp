#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

map<string, int> Transaction::counter = {};

Transaction::Transaction() {}
Transaction::~Transaction() {}

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