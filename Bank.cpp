#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include "Customer.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
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
    saveCusToFile("customers.txt");
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
    saveCusToFile("customers.txt");
    return true;
}

string Bank::addCHK(string ID, long long balance, long long overdraftLimit, tm openDate)
{
    Customer *cus = searchCustomer(ID);
    if (!cus) return "";
    Account* acc = new CheckingAccount(balance, overdraftLimit, openDate);
    string newID = cus->addAccount(acc);
    accounts.push_back(acc);
    saveAccToFile("accounts.txt");
    return newID;
}

string Bank::addSAV(string ID, long long balance, tm openDate)
{
    Customer *cus = searchCustomer(ID);
    if (!cus) return "";
    Account* acc = new SavingAccount(balance, openDate);
    string newID = cus->addAccount(acc);
    accounts.push_back(acc);
    saveAccToFile("accounts.txt");
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
    saveAccToFile("accounts.txt");
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
    saveTransToFile("transactions.txt");
}

bool Bank::withdraw(Account &a, double amount)
{
    if (a.getStatus() == "Closed") return false;

    if (a.withdraw(amount)) {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T = Transaction(a.getID(), "", ltm, amount, "withdraw", "success");
        transactions.push_back(T);
        a.addTransaction(T);
        saveTransToFile("transactions.txt");
        return true;
    } else {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T = Transaction(a.getID(), "", ltm, amount, "withdraw", "failed");
        transactions.push_back(T);
        a.addTransaction(T);
        saveTransToFile("transactions.txt");
        return false;
    }
}

bool Bank::transfer(Account &a, string ID, double amount)
{
    if (a.getStatus() == "Closed") return false;
    
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
        saveTransToFile("transactions.txt");
        return true;
    } else {
        time_t now = time(0);
        tm ltm = *localtime(&now);
        Transaction T1 = Transaction(a.getID(), ID, ltm, amount, "transfer_out", "failed");
        transactions.push_back(T1);
        a.addTransaction(T1);
        saveTransToFile("transactions.txt");
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
            saveCusToFile("customers.txt");
            saveAccToFile("accounts.txt");
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

int Bank::extractNumber(const string& id) {
    size_t pos = 0;
    while (pos < id.size() && !isdigit(id[pos])) {
        pos++;
    }
    return stoi(id.substr(pos));
}


void Bank::loadCusFromFile(const string& filename)
{
    ifstream in(filename);
    if (!in) return;

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, id, phone, email, address, n;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, phone, '|');
        getline(ss, email, '|');
        getline(ss, address);

        addCustomer(name, phone, email, address);
        cusNum = max(cusNum, extractNumber(id));
    }
}

void Bank::saveCusToFile(const string& filename)
{
    ofstream out(filename);
    for (auto& c: customers) {
        out << c.getID() << "|"
            << c.getName() << "|"
            << c.getPhone() << "|"
            << c.getEmail() << "|"
            << c.getAddress() << "\n";
    }
    out.close();
}

void Bank::loadAccFromFile(const string& filename)
{
    ifstream in(filename);
    if (!in) return;
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string type, temp;
        getline(ss, type, '|');

        if (type == "CHK") {
            string id, cusID;
            long long balance, overdraft;

            getline(ss, id, '|');
            getline(ss, temp, '|');
            getline(ss, cusID, '|');
            ss >> balance;
            ss.ignore();
            ss >> overdraft;
            auto openDate = stringToTm(temp);

            // SUA LOI: Khong dung addCHK (vi no sinh ID moi)
            // Tao truc tiep va setID lai tu file

            Customer* cus = searchCustomer(cusID);
            if (cus) {
                CheckingAccount* acc = new CheckingAccount(balance, overdraft, openDate);

                // Khoi phuc ID tu file
                acc->setID(id);
                // Cap nhat bo dem de lan sau khong sinh trung ID nay
                Account::updateCounter("checking", extractNumber(id));

                cus->addAccount(acc);
                accounts.push_back(acc);
            }
        }
        else if (type == "SAV") {
            string id, cusID;
            long long balance, term, minBal;
            double rate;

            getline(ss, id, '|');
            getline(ss, temp, '|');
            getline(ss, cusID, '|');
            ss >> balance;
            ss.ignore();
            ss >> rate;
            ss.ignore();
            ss >> term;
            ss.ignore();
            ss >> minBal;
            auto openDate = stringToTm(temp);

            addSAV(cusID, balance, openDate);
        }
    }
}

void Bank::saveAccToFile(const string& filename)
{
    ofstream out(filename);
    for (auto& acc : accounts) {
        out << acc->toFileString() << "\n";
    }
    out.close();
}

void Bank::loadTransFromFile(const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        Transaction t = Transaction::fromFileString(line);
        transactions.push_back(t);
        string tid = line.substr(line.find('|') + 1);
        tid = tid.substr(0, tid.find('|'));
        int num = extractNumber(tid);
        Transaction::updateCounter(t.getType(), num);
    }
}

void Bank::saveTransToFile(const string& filename) {
    ofstream out(filename);
    for (const auto& t : transactions)
        out << t.toFileString() << '\n';
}
void Bank::filterCustomer()
{
    long long minBalance;
    cout << "Nhap so du toi thieu: ";
    cin >> minBalance;

    for (auto& c : customers) {
        if (c.totalBalance() >= minBalance) {
            c.showInfo();
        }
    }
}

void Bank::sortCustomer()
{
    vector<Customer> temp = customers;
    sort(temp.begin(),temp.end(),
        [](Customer& a, Customer& b) {
            return a.totalBalance() > b.totalBalance();
        });
    
    for (auto& c : temp) {
        c.showInfo();
    }
}

void Bank::filterAccountByBalance()
{
    long long min;
    cout << "Nhap so du toi thieu: ";
    cin >> min;

    for (auto acc : accounts) {
        if (acc->getBalance() >= min) {
            acc->displayInfo();
        }
    }
}

void Bank::sortAccountBybalance()
{
    vector<Account*> temp = accounts;
    sort(temp.begin(), temp.end(),
        [](Account* a, Account* b) {
            return a->getBalance() < b->getBalance();
        }); 

    for (auto acc : temp) {
        acc->displayInfo();
    };
}
void Bank::filterTransactionByType()
{
    string type;
    cout << "Nhap loai giao dich: ";
    cin >> type;

    for (auto& t : transactions) {
        if (t.getType() == type)
            t.log();
    }
}
void Bank::filterAccountByID()
{
    string cid;
    cout << "Nhap ID khach hang: ";
    cin >> cid;

    bool found = false;
    for (auto acc : accounts) {
        if (acc->getID() == cid) {
            acc->displayInfo();
            found = true;
        }
    }

    if (!found)
        cout << "Khach hang chua co tai khoan!\n";
}
void Bank::filterAccountByDate(tm from, tm to)
{
    time_t A = mktime(&from), B = mktime(&to);
    bool found = false;
    for (auto acc : accounts) {
        tm d = acc->getopenDate();
        time_t current = mktime(&d);
        if (current >= A && current <= B) {
            acc->displayInfo();
            found = true;
        }
    }

    if (!found)
        cout << "Khong co tai khoan nao trong khoang thoi gian nay!\n";
}

void Bank::sortAccountByID()
{
    vector<Account*> temp = accounts;   // COPY

    sort(temp.begin(), temp.end(),
        [](Account* a, Account* b) {
            return a->getID() < b->getID();
        });

    for (auto acc : temp) {
        acc->displayInfo();
    }
}


void Bank::sortAccountByDate()
{
    vector<Account*> temp = accounts;

    sort(temp.begin(), temp.end(),
        [](Account* a, Account* b) {
            tm tempA = a->getopenDate();
            tm tempB = b->getopenDate();
            time_t A = mktime(&tempA);
            time_t B = mktime(&tempB);
            return A > B;
        });
    
    for (auto acc : temp) {
        acc->displayInfo();
    }
}
