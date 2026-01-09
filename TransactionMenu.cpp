#include "TransactionMenu.h"
#include "Bank.h"
#include "AccountMenu.h"
#include "Transaction.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

void firstRow()
{
    cout << left
        << setw(12) << "Ma GD"
        << setw(15) << "TK Nguon"
        << setw(15) << "TK Nhan"
        << setw(27) << "Thoi gian"
        << setw(15) << "So tien"
        << setw(20) << "Loai"
        << setw(10) << "Trang thai"
        << endl;
    cout << string(114, '-') << endl;
}

void filterByAccount(Bank &bank)
{
    string accID = checkAccount(bank);
    auto filter = bank.filterByID(accID);
    if (filter.empty()) {
        cout << "Khong co giao dich nao ca.\n";
        return;
    }
    firstRow();
    int n = filter.size();
    for (int i = 0; i < n; i++) filter[i].log();
}

void filterByType(Bank &bank)
{
    map <int, string> type = {{1, "deposit"}, {2, "withdraw"}, {3, "transfer_in"}, {4, "transfer_out"}};
    bool ok = false;
    int choice;

    do {
        cout << "Nhap loai giao dich (1-Deposit / 2-Withdraw / 3-Transfer in / 4-Transfer out): "; cin >> choice;
        cin.ignore();
        if (choice > 4 || choice < 1) {
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
            ok = false;
        }
        else ok = true;
    } while (!ok);

    auto filter = bank.filterByType(type[choice]);
    if (filter.empty()) {
        cout << "Khong co giao dich nao ca.\n";
        return;
    }
    firstRow();
    int n = filter.size();
    for (int i = 0; i < n; i++) filter[i].log();
}

void filterByDate(Bank &bank)
{
    tm from = {}, to = {};
    cout << "Nhap ngay bat dau (dd mm yyyy): ";
    cin >> from.tm_mday >> from.tm_mon >> from.tm_year;
    cout << "Nhap ngay ket thuc (dd mm yyyy): ";
    cin >> to.tm_mday >> to.tm_mon >> to.tm_year;

    from.tm_mon -= 1;
    from.tm_year -= 1900;

    to.tm_mon -= 1;
    to.tm_year -= 1900;
    to.tm_hour = 23;
    to.tm_min = 59;
    to. tm_sec = 59;

    auto filter = bank.filterByDate(from, to);
    if (filter.empty()) {
        cout << "Khong co giao dich nao ca.\n";
        return;
    }
    firstRow();
    int n = filter.size();
    for (int i = 0; i < n; i++) filter[i].log();
}

void statisticsMenu(Bank &bank)
{
    system("cls");
   int choice;
    do {
        cout << "\n----- THONG KE -----\n";
        cout << "1. Thong ke khach hang\n";
        cout << "2. Thong ke tai khoan\n";
        cout << "3. Thong ke giao dich\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                int totalCus, noAcc;
                string mostAccCusID, richestCusID;
                long long maxTotalBalance;
                bank.customerStatistics(totalCus, noAcc, mostAccCusID, richestCusID, maxTotalBalance);

                cout <<"\n--- THONG KE KHACH HANG---\n";
                cout << "Tong so khach hang: " << totalCus << endl;
                cout << "So khach hang khong co tai khoan: " << noAcc << endl;
                cout << "Khach hang nhieu tai khoan nhat: " << mostAccCusID << endl;
                cout << "Khach hang co so du lon nhat: " << richestCusID << endl;
                cout << "Tong so du: " << maxTotalBalance << endl;
                break;
            }
            case 2: {
                int totalAcc, checkingCnt, savingCnt, overdraftCnt;
                long long totalBal, maxBal;
                string maxBalAccID;

                bank.accountStatistics(totalAcc, checkingCnt, savingCnt, overdraftCnt, totalBal, maxBal, maxBalAccID);
                
                cout << "\n--- THONG KE TAI KHOAN ---\n";
                cout << "Tong so tai khoan: " << totalAcc << endl;
                cout << "CheckingAccount: " << checkingCnt << endl;
                cout << "SavingAccount: " << savingCnt << endl;
                cout << "Tong so du he thong: " << totalBal << endl;
                cout << "Tai khoan co so du cao nhat: "
                    << maxBalAccID << " | " << maxBal << endl;
                cout << "So tai khoan bi am (overdraft): "
                    << overdraftCnt << endl;
                break;
            }
            case 3: {
                int deposit = 0, withdraw = 0, transfer = 0, success = 0, failed = 0;
                bank.countTransactions(deposit, withdraw, transfer);
                bank.successRate(success, failed);

                cout <<"\n--- THONG KE GIAO DICH---\n";
                cout << "So giao dich nap: " << deposit << endl;
                cout << "So giao dich rut: " << withdraw << endl;
                cout << "So giao dich chuyen: " << transfer << endl;
                cout << "Tong so giao dich: " << deposit + withdraw + transfer << endl;
                cout << "Thanh cong: " << success << endl;
                cout << "That bai: " << failed << endl;
                cout << "Ty le: " << fixed << setprecision(2) << (success)/(success + failed)*100 << "%" << endl;
                break;
            }
        }
    } while (choice != 0);  
}

void transactionSortMenu(Bank &bank)
{
    system("cls");
    int choice;
    do {
        cout << "\n--- SAP XEP GIAO DICH ---\n";
        cout << "1. Theo thoi gian (cu -> moi)\n";
        cout << "2. Theo thoi gian (moi -> cu)\n";
        cout << "3. Theo so tien (tang dan)\n";
        cout << "4. Theo so tien (giam dan)\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        vector<Transaction> sorted;

        switch (choice) {
            case 1: {
                sorted = bank.sortTransaction(1);
                break;
            } case 2: {
                sorted = bank.sortTransaction(2);
                break;
            } case 3: {
                sorted = bank.sortTransaction(3);
                break;
            } case 4: {
                sorted = bank.sortTransaction(4);
                break;
            }
        }

        firstRow();
        for (auto t : sorted) t.log();

    } while (choice != 0);
}