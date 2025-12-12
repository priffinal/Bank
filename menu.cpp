#include "menu.h"
#include<iostream>
using namespace std;
void menu::drawFrame() {
    for (int i = 0; i < 30; i++) cout << "=";
    cout << "\n";
}

void menu::clearScreen() {
    system("cls");
}

void menu::showMainMenu() {
    clearScreen();
    drawFrame();
    cout << "      NGAN HANG SO TDPBANK\n";
    drawFrame();

    cout << "[1] Tao tai khoan\n";
    cout << "[2] Rut tien\n";
    cout << "[3] Chuyen khoan\n";
    cout << "[4] Xem danh sach\n";
    cout << "[0] Thoat\n";
    drawFrame();
    cout << "Nhap lua chon: ";
}
