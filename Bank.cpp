#include "Bank.h"
#include "AutoGen.h"
#include <iostream>
#include <ctime>
using namespace std;

int Bank::cusNum = 0;

Bank::Bank(){}
Bank::~Bank(){}

string Bank::addCustomer(string name, string phone, string email, string address)
{
    Customer c;
    c.createCustomer(name, phone, email, address);
    c.autoID(autoGenerate("C", ++cusNum));
    customers.push_back(c);
    return c.getID();
}

Customer* Bank::searchCustomer(const string &ID) {
    for (auto& c : customers) {
        if (c.getID() == ID) {
            return &c;
        }
    }
    return nullptr;
}

bool Bank::showCusInfo(string ID)
{
    Customer* cus = searchCustomer(ID);
    if (!cus) return false;
   cus->showInfo();
   return true;
}

bool Bank::updateCusInfo(string ID, string name, string phone, string email, string address)
{
    Customer* cus = searchCustomer(ID);
    if (!cus) return false;
    cus->updateInfo(name, phone, email, address);
    return true;
}

string Bank::addCHK(string ID, long long balance, long long overdraftLimit)
{
    Customer *cus = searchCustomer(ID);
    if (!cus) return "";
    Account* acc = new CheckingAccount(balance, overdraftLimit);
    string newID = cus->addAccount(acc);
    accounts.push_back(acc);
    return newID;
}

string Bank::addSAV(string ID, long long balance)
{
    Customer *cus = searchCustomer(ID);
    if (!cus) return "";
    Account* acc = new SavingAccount(balance);
    string newID = cus->addAccount(acc);
    accounts.push_back(acc);
    return newID;
}

Account* Bank::searchAccount(const string& ID) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->getID() == ID) {
            return accounts[i];
        }
    }
    return nullptr;
}

void Bank::closeAccount(string accID)
{
    Account *acc = searchAccount(accID);
    acc->closeAccount();
}

bool Bank::showAccInfo(string ID)
{
    Account* acc = searchAccount(ID);
    if (acc == nullptr) return false;
    acc->displayInfo();
    return true;
}

void Bank::deposit(Account &a, double amount)
{
    a.deposit(amount);
    time_t now = time(0);
    tm ltm = *localtime(&now);
    Transaction T = Transaction(a.getID(), "", ltm, amount, "deposit", "success");
    transactions.push_back(T);
}

bool Bank::withdraw(Account &a, double amount)
{
    if (a.withdraw(amount)) {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T = Transaction(a.getID(), "", ltm, amount, "withdraw", "success");
        transactions.push_back(T);
        return true;
    } else {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T = Transaction(a.getID(), "", ltm, amount, "withdraw", "failed");
        transactions.push_back(T);
        return false;
    }
}

bool Bank::transfer(Account &a, string ID, double amount)
{
    if (a.transfer_out(amount, ID)) {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        transactions.push_back(Transaction(a.getID(), ID, ltm, amount, "transfer_out", "success"));
        searchAccount(ID)->transfer_in(amount, a.getID());
        transactions.push_back(Transaction(a.getID(), ID, ltm, amount, "transfer_in", "success"));
        return true;
    } else {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        transactions.push_back(Transaction(a.getID(), ID, ltm, amount, "transfer_out", "failed"));
        transactions.push_back(Transaction(a.getID(), ID, ltm, amount, "transfer_in", "failed"));
        return false;
    }
}

bool Bank::deleteCustomer(string ID)
{
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getID() == ID) {
            customers[i] = customers.back();
            customers.pop_back();
            customers[i].removeAllAccount();
            return true;
        }
    } return false;
}


long long Bank::totalDeposit()
{
    long long sum = 0;
    for (auto t : transactions) {
        if (t.getType() == "deposit") sum += t.getAmount();
    }
    return sum;
}

long long Bank::totalWithdraw(string ID)
{
    double sum = 0;
    for (auto t : transactions) {
        if (t.getType() == "withdraw" && t.getAccID() == ID) {
            sum += t.getAmount();
        } 
    }
    return sum;
}

vector<Transaction> Bank::filterByDate(tm from, tm to) 
{
    vector<Transaction> result;
    time_t t1 = mktime(&from);
    time_t t2 = mktime(&to);
    if (t1 == -1 || t2 == -1) return result;
    for (auto& tr : transactions) {
        tm temp = tr.getTime();
        time_t tt = mktime(&temp);
        if (tt != -1 && tt >= t1 && tt <= t2) {
            result.push_back(tr);
        }
    }
    return result;
}

void Bank::printAllTransactions()
{
    for (int i = 0; i < transactions.size(); i++) {
        transactions[i].log();
    }
}