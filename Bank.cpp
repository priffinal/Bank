#include "Bank.h"
#include "AutoGen.h"
#include "Customer.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include <iostream>
#include <ctime>
#include <algorithm>
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
    a.addTransaction(T);
}

bool Bank::withdraw(Account &a, double amount)
{
    if (a.withdraw(amount)) {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T = Transaction(a.getID(), "", ltm, amount, "withdraw", "success");
        transactions.push_back(T);
        a.addTransaction(T);
        return true;
    } else {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T = Transaction(a.getID(), "", ltm, amount, "withdraw", "failed");
        transactions.push_back(T);
        a.addTransaction(T);
        return false;
    }
}

bool Bank::transfer(Account &a, string ID, double amount)
{
    if (a.transfer_out(amount, ID)) {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T1 = Transaction(a.getID(), ID, ltm, amount, "transfer_out", "success");
        transactions.push_back(T1);
        a.addTransaction(T1);
        searchAccount(ID)->transfer_in(amount, a.getID());
        Transaction T2 = Transaction(a.getID(), ID, ltm, amount, "transfer_in", "success");
        transactions.push_back(T2);
        searchAccount(ID)->addTransaction(T2);
        return true;
    } else {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T1 = Transaction(a.getID(), ID, ltm, amount, "transfer_out", "failed");
        transactions.push_back(T1);
        a.addTransaction(T1);
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

vector<Transaction> Bank::filterByID(string ID)
{
    vector<Transaction> result;
    int n = transactions.size();
    for (int i = 0; i < n; i++) {
        if (transactions[i].getAccID() == ID) {
            result.push_back(transactions[i]);
        }
    }
    return result;
}

vector<Transaction> Bank::filterByType(string type)
{
    vector<Transaction> result;
    int n = transactions.size();
    for (int i = 0; i < n; i++) {
        if (transactions[i].getType() == type) {
            result.push_back(transactions[i]);
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

void Bank::countTransactions(int &n1, int &n2, int &n3)
{
    n1 = n2 = n3 = 0;
    for (auto &tr : transactions) {
        if (tr.getType() == "deposit") n1++;
        if (tr.getType() == "withdraw") n2++;
        if (tr.getType() == "transfer_in") n3++;
    }
}

void Bank::successRate(int &n1, int &n2)
{
    n1 = n2 = 0;
    for (auto &tr : transactions) {
        if (tr.getStatus() == "success") n1++;
        if (tr.getStatus() == "failed") n2++;
    }
}

void Bank::customerStatistics(int &totalCus, int &noAcc, string &mostAccCusID, string &richestCusID, long long &maxTotalBalance)
{
    totalCus = (int)customers.size();
    noAcc = 0;
    maxTotalBalance = 0;

    if (!customers.empty()) {
        mostAccCusID = customers[0].getID();
        richestCusID = customers[0].getID();
    } else {
        mostAccCusID = "";
        richestCusID = "";
    }

    for (auto &cus : customers) {
        if (cus.getAccountCount() == 0) noAcc++;

        if (!mostAccCusID.empty() && cus.getAccountCount() > searchCustomer(mostAccCusID)->getAccountCount()) mostAccCusID = cus.getID();

        if (!richestCusID.empty() && cus.totalBalance() > searchCustomer(richestCusID)->totalBalance()) richestCusID = cus.getID();

        maxTotalBalance += cus.totalBalance();
    }
}

void Bank::accountStatistics(int &totalAcc, int &checkingCnt, int &savingCnt, int &overdraftCnt, long long &totalBalance,
                             long long &maxBalance, string &maxBalAccID)
{
    totalAcc = (int)accounts.size();
    checkingCnt = savingCnt = overdraftCnt = 0;
    totalBalance = 0;
    maxBalance = LLONG_MIN;
    maxBalAccID = "";

    if (!accounts.empty()) {
        maxBalAccID = accounts[0]->getID();
        maxBalance = accounts[0]->getBalance();
    }
    
    for (auto acc : accounts) {
        if (acc->getID().substr(0, 3) == "CHK") checkingCnt++;

        if (acc->getID().substr(0, 3) == "SAV") savingCnt++;

        if (acc->getBalance() < 0) overdraftCnt++;

        totalBalance += acc->getBalance();

        if (acc->getBalance() > maxBalance) {
            maxBalAccID = acc->getID();
            maxBalance = acc->getBalance();
        }
    }
}

vector<Transaction> Bank::sortTransaction(int type)
{
    vector<Transaction> result = transactions;

    switch (type) {

    case 1:
        sort(result.begin(), result.end(),
            [](Transaction a, Transaction b) {
                tm tempA = a.getTime();
                tm tempB = b.getTime();
                time_t A = mktime(&tempA);
                time_t B = mktime(&tempB);
                return A < B;
            });
        break;

    case 2:
        sort(result.begin(), result.end(),
            [](Transaction a, Transaction b) {
                tm tempA = a.getTime();
                tm tempB = b.getTime();
                time_t A = mktime(&tempA);
                time_t B = mktime(&tempB);
                return A > B;
            });
        break;

    case 3:
        sort(result.begin(), result.end(),
            [](Transaction a, Transaction b) {
                return a.getAmount() < b.getAmount();
            });
        break;

    case 4:
        sort(result.begin(), result.end(),
            [](Transaction a, Transaction b) {
                return a.getAmount() > b.getAmount();
            });
        break;
    }

    return result;
}