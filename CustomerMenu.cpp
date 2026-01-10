#include "CustomerMenu.h"
#include "Customer.h"
#include <iostream>
#include "choice.h"

using namespace std;

void addCustomer(Bank &bank)
{
    string fullName, phone, email, address;
    //cin.ignore(1000, '\n');
    cout << "Nhap ho ten: ";
    getline(cin, fullName);
    cout << "Nhap so dien thoai: ";
    getline(cin, phone);
    cout << "Nhap email: ";
    getline(cin, email);
    cout << "Nhap dia chi: ";
    getline(cin, address);

    string newID = bank.addCustomer(fullName, phone, email, address);
    cout << "Tao khach hang thanh cong.\n";
    cout << "ID cua khach hang la: " << newID << endl;
}

string checkCustomer(Bank &bank)
{
    bool ok = false;
    string ID;
    do {
        cout << "Nhap ID khach hang: ";
        cin >> ID;
      //  cin.ignore();
        cin.ignore(1000, '\n');
        if (bank.searchCustomer(ID) == nullptr) {
            cout << "Khong the tim thay doi tuong. Vui long nhap lai.\n";
            ok = false;
        } 
        else ok = true;
    } while (!ok);
    return ID;
}

void editCusInfo(Bank &bank)
{
    string ID = checkCustomer(bank);
    string name, phone, email, address;
    cin.ignore(1000, '\n');
    cout << "Sua thong tin (khong sua thi an Enter)\n";
    cout << "Sua ten: "; getline(cin, name);
    cout << "Sua SDT: "; getline(cin, phone);
    cout << "Sua email: "; getline(cin ,email);
    cout << "Sua dia chi: "; getline(cin, address);
    bank.updateCusInfo(ID, name, phone, email, address); 

}

void showCusInfo(Bank &bank)
{
    string ID = checkCustomer(bank);
    auto cus = bank.searchCustomer(ID);
    cus->showInfo();
}

void deleteCustomer(Bank &bank)
{
    string ID = checkCustomer(bank);
    bank.deleteCustomer(ID);
    cout << "Xoa khach hang thanh cong.\n";
}
